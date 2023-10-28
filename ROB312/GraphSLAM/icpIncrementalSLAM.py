"""
 Incremental ICP SLAM  - Basic implementation for teaching purpose only...
 Computes position of each scan with respect to closest one in the
 current map and add scan to the map if it is far enough from all the
 existing ones
 author: David Filliat
"""

import readDatasets as datasets
import matplotlib.pyplot as plt
import icp
import numpy as np
import copy


# Reading data
scan_list = datasets.read_fr079(0)
axis_limit = [-20, 25, -10, 30]
#scan_list = datasets.read_u2is(0)
#axis_limit = [-5.5, 12.5, -12.5, 6.5]

# Parameters for scan processing
min_scan = 0
step = 3
max_scan = 550#len(scan_list) - step

# Parameters for map building
dist_threshold_add = 0.3

# Copy for reference display and map init
odom_scan_list = copy.deepcopy(scan_list)
map = [scan_list[min_scan]]

# Init displays
f, (ax1, ax2) = plt.subplots(1, 2, sharey=True, figsize=(14, 7))
c = np.random.rand(3,)
ax1.scatter(odom_scan_list[min_scan]["x"],
            odom_scan_list[min_scan]["y"], color=c, s=1)
ax1.axis(axis_limit)
ax1.set_title('Pose from raw odometry')
ax2.scatter(map[0]["x"], map[0]["y"], color=c, s=1)
ax2.axis(axis_limit)
ax2.set_title('Map after incremental ICP SLAM')
plt.pause(0.1)

# Perform incremental SLAM
for i in range(min_scan + step, max_scan, step):

    # get list of map scan sorted by distance
    sorted_dist, sorted_id = datasets.find_closest_scan(map, scan_list[i])
    ref_scan_id = sorted_id[0]
    print('Matching new scan to reference scan ' + str(ref_scan_id))

    # perform ICP with closest scan
    R, t, error = icp.icp(map[ref_scan_id], scan_list[i], 200, 1e-7)

    # Correct all future scans odometry pose
    for j in range(i, max_scan, step):
        scan_list[j] = datasets.transform_scan(scan_list[j], R, t)

    # Add scan to map if it is far enough
    if np.linalg.norm(scan_list[i]["pose"][0:2] -
                      map[ref_scan_id]["pose"][0:2]) > dist_threshold_add:
        map.append(scan_list[i])
        print('Added to map, new size : ' + str(len(map)))

        # Map display
        ax2.cla()
        for scan in map:
            c = np.random.rand(3,)
            ax2.scatter(scan["x"], scan["y"], color=c, s=1)
            ax2.scatter(scan["pose"][0],
                        scan["pose"][1], color=c, s=3)
        ax2.axis(axis_limit)
        ax2.set_title('Map after incremental ICP SLAM')

    # Scan display
    c = np.random.rand(3,)
    ax1.scatter(odom_scan_list[i]["x"],
                odom_scan_list[i]["y"], color=c, s=1)
    ax1.scatter(odom_scan_list[i]["pose"][0],
                odom_scan_list[i]["pose"][1], color=c, s=3)
    plt.pause(0.1)

plt.savefig('ICPIncrementalSLAM.png')
print("Press Q in figure to finish...")
plt.show()
