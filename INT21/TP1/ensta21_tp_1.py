# -*- coding: utf-8 -*-
"""ENSTA21-TP-1.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1LZgg5NIWX48Kx-9emkwutl62u8uKeOZ-

# First TP
In this tutorial, you will compare the efficiency of a purely random search against evolutionary optimization, on two case studies: the [Weierstrass function](https://en.wikipedia.org/wiki/Weierstrass_function) and the [Rastrigin function](https://en.wikipedia.org/wiki/Rastrigin_function). Both are relatively simple, but finding the global minimum for each is not straightforward. Below is the code for both.
"""

import matplotlib.pyplot as plt
import numpy as np

def weierstrass(X):
    b = 2.5
    h = 0.5
    i = 20

    f = 0
    for k in range(1,i+1):
        f2 = 0
        for x in X:
            f2 += 1- np.cos(np.power(b,k)*x)

        f += np.power(b,-h*k)*f2
    return f


def rastrigin(X):
    return 10 * len(X) + sum([x**2 - 10 * np.cos(2*np.pi*x) for x in X])

# this is a plot in one dimension
X_original = np.arange(-1, 1, 0.01)
X = [ [x] for x in X_original ]
y = [ weierstrass(x) for x in X ]
fig = plt.figure()
plt.plot(X_original, y, label="Weierstrass Function")
plt.xlabel("x")
plt.ylabel("y")
plt.legend(loc='best')

y = [ rastrigin(x) for x in X ]
fig2 = plt.figure()
plt.plot(X_original, y, 'r', label="Rastrigin Function")
plt.xlabel("x")
plt.ylabel("y")
plt.legend(loc='best')

"""Here below is the code for a purely random optimization function, that generates random inputs (X) for a function, and stores the lowest output (y) obtained so far."""

def random_search(n_dimensions, n_evaluations, min_bound, max_bound, cost_function, generator):
    #n_dimensions = Nombre de dimensions, n_evaluations = nombre de points à évaluer, min_bound = bornes min, max_bound = bornes max
    #cost_function = Fonction sur laquelle on optimise

    # Initialisation
    best_fit = np.Inf
    best_fit_during_run = []

    for i in range(n_evaluations):
        X = [ generator.uniform(min_bound, max_bound) for i in range(n_dimensions) ]
        fit = cost_function(X) #Calcul de la fitness

        if(fit < best_fit):
            best_fit = fit #bestFit = Meilleure fitness vue jusque là

        best_fit_during_run.append(best_fit) # On stocke ici la meilleure fitness vue à chaque évaluation

    return best_fit_during_run

"""Random number generation in computer science is not exactly "random"; there are algorithms called "pseudo-number generators" that can generate long sequences of numbers, but eventually they will start repeating. Moreover, by fixing a "random seed", we can guarantee that the sequence will be the same every time the algorithm is run. Fixing the "random seed" can be useful to obtain repeatable experiments. Exact details of pseudo-random number generation are outside of the scope of this class; if you'd like to know more, a good starting point is [the Wikipedia page](https://en.wikipedia.org/wiki/Pseudorandom_number_generator)."""

from random import Random
generator = Random() # create instance of pseudo-random number generator
generator.seed(42) # fixes the seed, so that the same sequence of numbers is generated, at each run; commenting this line seeds the generator with system time, giving you different sequences at every run
print("The first number in the pseudo-random sequence is: %.4f" % generator.random())

"""Now, try running the code below, that applies the random search function to Weierstrass, and see what is the best result you can get. Run the function multiple times, what do you notice?"""

number_of_evaluations = 1000
number_of_dimensions = 5
random_values = random_search(5, number_of_evaluations, -1, 1, weierstrass, generator) # cost function can also be changed to 'rastrigin'
print("The best solution found after %d evaluations is: %.2f" % (number_of_evaluations, random_values[-1])) # the best value is last in the list

"""In this next step, we implement our first evolutionary algorithm. The code presented below at the moment is performing just a random search. Try running it a few times, and you will see that the results are not very different from the previous **random_search** function.

Try implementing a mutation operator, where the comments indicate it should placed. The mutation operator should create new individuals/candidate solutions by modifying existing ones. For example, your could choose one variable of one candidate solution and modify it by a small value, creating a new candidate solution. Or perform small variations of several variables of the same candidate solution at the same time.

The results you get should be better than by simply using random search.
"""

def evolutionary_algorihtm(n_dimensions, max_evaluations, min_bound, max_bound, cost_function, generator, pop_size, offspring_size=None) :

  # store number of evaluations
  n_evaluations = 0
  # also store best fitness/cost function value at each evaluation
  best_fitness_history = []

  # if size of the offspring is not specified, let's set it to 2 times the population
  if offspring_size is None : offspring_size = 2 * pop_size

  # generate initial random population
  print("Creating initial population of size %d..." % pop_size)
  population = []
  for i in range(pop_size) :
    individual = [ generator.uniform(min_bound, max_bound) for j in range(n_dimensions) ]
    population.append([0.0, individual]) # each entry in the population is a tuple with fitness value (initially zero) and individual

  # evaluate individuals in initial population
  print("Evaluating initial population...")
  for individual in population :
    individual[0] = cost_function(individual[1]) # fitness value for the individual is the value of the cost function for that individual's genome
    n_evaluations += 1
  
  # these two lines are just to get a history of the fitness values, to be later compared
  population = sorted(population, key = lambda x : x[0]) # sort elements based on entry [0], which is the fitness value
  best_fitness_history = [ population[0][0] ] * pop_size
  
  # while the stop condition is not reached, keep iterating
  while n_evaluations < max_evaluations :

    for i in range(offspring_size) :
      # tournament selection of size two
      # select a "parent" individual by picking two random individuals in the population, and choosing the one with the best fitness
      candidate_parent_1 = population[generator.randint(0, len(population)-1)]
      candidate_parent_2 = population[generator.randint(0, len(population)-1)]

      parent = candidate_parent_1[1]
      if candidate_parent_2[0] < candidate_parent_1[0] : # we assume we are minimizing, so lower fitness is better
        parent = candidate_parent_2[1]
      
      # TODO: create a mutation operator that generates a child individual by randomly modifying the parent
      # TODO: remember that to copy a list in Python, you need to use the "copy" method, like child = parent.copy() 
      # TODO: right now, the algorithm is just creating a completely random individual, like random search
      child = [ generator.uniform(min_bound, max_bound) for j in range(n_dimensions) ]

      # evaluate the child
      child_fitness = cost_function(child)
      n_evaluations += 1

      # add child to population
      population.append([child_fitness, child])
    
    # now that all offspring have been created, let's sort the population and remove the worst individuals, resizing the population to the initial pop_size
    population = sorted(population, key = lambda x : x[0]) # sort elements based on entry [0], which is the fitness value
    population = population[0:pop_size] # remove all individuals beyond pop_size
    print("Best cost function value/fitness so far: %.2f" % population[0][0])

    # store information in the fitness history
    best_fitness_history.extend( [population[0][0]] * offspring_size)
  
  print("Evolution finished: performed a total of %d evaluations" % n_evaluations)
  return population, best_fitness_history

# run the evolutionary algorithm
population, best_fitness_history = evolutionary_algorihtm(number_of_dimensions, number_of_evaluations, -1, 1, weierstrass, generator, 100)
print("The best value found for the cost function is %.2f" % population[0][0])

"""We can compare the performance of the algorithms using a graph, showing what happens as the number of evaluations increases."""

import matplotlib.pyplot as plt
fig = plt.figure()
plt.plot(range(0, len(random_values)), random_values, 'r-', label="Random search")
plt.plot(range(0, len(best_fitness_history)), best_fitness_history, 'g-', label="Evolutionary algorithm")
plt.legend(loc='best')
plt.xlabel("Number of evaluations")
plt.ylabel("Best value of the cost function")

"""Random search and Evolutionary Algorithms are two among many optimization techniques. Another popular algorithm is **gradient descent**, that attempts to find the slope in a function, and follow it up to a point of minimum. Here we will use the implementation contained in the **scipy** package. Try running gradient descent multiple times.

The exact working of gradient descent is again outside of the scope of this class, but for more information, you can refer to [this Wikipedia page](https://en.wikipedia.org/wiki/Broyden%E2%80%93Fletcher%E2%80%93Goldfarb%E2%80%93Shanno_algorithm).
"""

from scipy.optimize import minimize
# we need to select a random starting point
starting_X = [ generator.uniform(-1, 1) for i in range(number_of_dimensions) ]
gradient_descent_result = minimize(weierstrass, x0=starting_X, method='L-BFGS-B')
gradient_descent_best_value = weierstrass(gradient_descent_result.x)
gradient_descent_evaluations = gradient_descent_result.nfev
print("Best value found by gradient descent after %d evaluations: %.2f" % (gradient_descent_evaluations, gradient_descent_best_value))

"""On smooth functions, gradient descent is fast and effective. However, both Weierstrass and Rastrigin are very difficult to tackle, because the information that gradient descent obtains from the derivative can be deceptive. 

![alt text](https://3qeqpr26caki16dnhd19sv6by6v-wpengine.netdna-ssl.com/wp-content/uploads/2018/12/Example-of-Local-and-Global-Minima-on-an-Error-Surface.png)

When a function has more than one minimum (e.g. local minima), gradient descent can get "stuck" into a local minimum and be unable to escape.

# Advanced tweaking of Evolutionary Algorithms
For the last part of this tutorial, you can implement a **crossover operator** for the evolutionary algorithm.

As a reminder, a crossover operator generates new candidate solutions starting from two 'parents'. One (or more) cut points are selected on the two parents, and the values of the parents are swapped, creating two new candidate solutions.

Then, try assigning a different probability of activation to the mutation operator you have already implemented, and the new crossover, so that one or the other (or even both!) can be activated at each iteration. You can then proceed to compare the performance of random search, gradient descent, and the evolutionary algorithm on a test function, when given the same number of evaluations.

Furthermore, test what happens when setting different parameters (**b**, **h**, **i**) for the Weierstrass function, observing how the shape of the function changes, and how it becomes easier/more difficult to find the global optimum for the different algorithms. Be careful, the parameters can vary only in a certain range, [see the Wikipedia page for more information](https://en.wikipedia.org/wiki/Weierstrass_function).

Finally, design a test plan to find the best parameters for the evolutionary algorithm: the parameters include $\mu$ (population size), $\lambda$ (offspring size), $\tau$ (size of the tournament selection to choose parents), probability of activation for the mutation, probability of activation for the crossover.
"""