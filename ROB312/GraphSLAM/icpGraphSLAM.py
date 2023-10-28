"""
 Graph SLAM with ICP - Basic implementation for teaching purpose only...
 Computes position of each scan with respect to several scans in the
 current map by optimizing the graph of relative positions
 author: David Filliat
"""

import readDatasets as datasets
import matplotlib.pyplot as plt
import icp
import numpy as np
import copy
import math


# Reading data
scan_list = datasets.read_fr079(0)
axis_limit = [-20, 25, -10, 30]
#scan_list = datasets.read_u2is(0)
#axis_limit = [-5.5, 12.5, -12.5, 6.5]

# Parameters for scan processing
min_scan = 0
step = 3
max_scan = 200#len(scan_list) - step

# Parameters for map building
dist_threshold_add = 0.1
dist_threshold_match = 0.8
max_ICP_error = 0.6

# Copy for reference display and map init
odom_scan_list = copy.deepcopy(scan_list)
map = [scan_list[min_scan]]

# Initialize graph of relative positions
# simple representation using matrixes
max_size = int(np.around((max_scan - min_scan)/step))
graph_theta = np.zeros((max_size, max_size)) # Change in robot direction between two nodes
graph_d = np.zeros((max_size, max_size)) # distance between two nodes
graph_phi = np.zeros((max_size, max_size)) # direction of motion between two nodes, relative to the 1st node pose


# Init displays
f, (ax1, ax2) = plt.subplots(1, 2, sharey=True, figsize=(14, 7))
c = np.random.rand(3,)
ax1.scatter(odom_scan_list[min_scan]["x"],
            odom_scan_list[min_scan]["y"], color=c, s=1)
ax1.scatter(odom_scan_list[min_scan]["pose"][0],
            odom_scan_list[min_scan]["pose"][1], color=c, s=3)
ax1.axis(axis_limit)
ax1.set_title('Poses from raw odometry')
ax2.scatter(map[0]["x"], map[0]["y"], color=c, s=1)
ax2.scatter(map[0]["pose"][0],
            map[0]["pose"][1], color=c, s=3)
ax2.axis(axis_limit)
ax2.set_title('Map after ICP Graph SLAM')
plt.pause(0.1)


# Process scans
for i in range(min_scan + step, max_scan, step):

    print('Processing scan ' + str(i))

    # get list of map scan sorted by distance
    sorted_dist, sorted_id = datasets.find_closest_scan(map, scan_list[i])

    # Keep only the ones below the distance threshold, or the closest one
    close_scans = sorted_id[sorted_dist < dist_threshold_match]
    if len(close_scans) == 0:
        close_scans = [sorted_id[0]]

    # perform ICP with closest scan to correct future odometry
    #R, t, error, iter = icp.icp(map[close_scans[0]], scan_list[i], 200, 1e-7)
    R, t, error = icp.icp(map[close_scans[0]], scan_list[i], 200, 1e-7)

    # Correct all future scans odometry pose
    for j in range(i, max_scan, step):
        scan_list[j] = datasets.transform_scan(scan_list[j], R, t)

    # --- Add scan to map and update graph if needed
    if np.linalg.norm(scan_list[i]["pose"][0:2] -
                      map[close_scans[0]]["pose"][0:2]) > dist_threshold_add:

        map.append(scan_list[i])
        print('Adding new scan with links to : ' + str(close_scans))

        # Get ref to last scan in map (i.e. new scan)
        id_new = len(map) - 1
        s_new = map[-1]

        # ---- Build graph
        edge_NB = 0
        for id_ref in close_scans:
            print("Adding edge")
            # take the reference scan among the closest map scan
            s_ref = map[id_ref]

            # compute position of new scan wrt the ref scan
            #Ri, ti, error, iter = icp.icp(s_ref, s_new, 200, 1e-7)
            Ri, ti, error = icp.icp(s_ref, s_new, 200, 1e-7)

            if error < max_ICP_error or edge_NB == 0:
                edge_NB += 1
                # compute absolute position of new scan
                s_new_corrected = datasets.transform_scan(s_new, Ri, ti)

                # compute relative pose with ref scan
                delta_theta = icp.angle_wrap(s_new_corrected["pose"][2] - s_ref["pose"][2])
                delta_t = s_new_corrected["pose"][0:2] - s_ref["pose"][0:2]

                # Add relative position of new scan wrt. ref scan pose in the graph
                graph_theta[id_ref, id_new] = delta_theta
                graph_d[id_ref,id_new] = np.linalg.norm(delta_t)
                graph_phi[id_ref,id_new] = np.arctan2(delta_t[1],delta_t[0]) - s_ref["pose"][2]

                # Fill the reverse direction in the graph
                graph_theta[id_new, id_ref] = - graph_theta[id_ref, id_new]
                graph_d[id_new,id_ref] = graph_d[id_ref,id_new]
                graph_phi[id_new,id_ref] = math.pi + np.arctan2(delta_t[1],delta_t[0]) - s_new_corrected["pose"][2]
                

        # --- Optimize graph until updates fall below threshold
        update_max = 1
        update_NB = 0
        while ( update_max > 1e-5 and update_NB < 500):
            update_max = 0
            update_NB += 1

            # Recompute each scan pose from its neighbors
            for k in range(len(map)):
                # Create a list of scan pose computed through neighbor pose and
                # relative position
                new_pose_list = []
                for l in range(len(map)):
                    if graph_d[l, k] != 0:
                        newAngle = icp.angle_wrap(map[l]["pose"][2] + graph_theta[l, k])
                        angle_link = map[l]["pose"][2] + graph_phi[l, k]
                        newX = map[l]["pose"][0] + graph_d[l, k] * math.cos(angle_link)
                        newY = map[l]["pose"][1] + graph_d[l, k] * math.sin(angle_link)
                        
                        new_pose_list.append(newX)
                        new_pose_list.append(newY)
                        new_pose_list.append(newAngle)

                # Compute new pose as mean of positions from neighbors and update map
                new_pose = np.array([np.mean(new_pose_list[0::3]),
                                    np.mean(new_pose_list[1::3]),
                                    icp.mean_angle(new_pose_list[2::3])])
                update = abs(new_pose.reshape(-1) - map[k]["pose"].reshape(-1))
                map[k] = datasets.update_scan_pose(map[k], new_pose)
                update_max = max(max(update), update_max)

        print('New map size : ' + str(len(map)) + ', Graph Updates : ' + str(update_NB))

    # Display
    c = np.random.rand(3,)
    ax1.scatter(odom_scan_list[i]["x"],
                odom_scan_list[i]["y"], color=c, s=1)
    ax1.scatter(odom_scan_list[i]["pose"][0],
                odom_scan_list[i]["pose"][1], color=c, s=3)
    ax2.cla()
    for scan in map:
        c = np.random.rand(3,)
        ax2.scatter(scan["x"], scan["y"], color=c, s=1)
        ax2.scatter(scan["pose"][0],
                    scan["pose"][1], color=c, s=3)
    ax2.axis(axis_limit)
    ax2.set_title('Map after ICP Graph SLAM')
    plt.pause(0.1)

plt.savefig('ICPGraphSLAM.png')
#print("Press Q in figure to finish...")
#plt.show()
