# 42-philosophers
<h1 align="center">
	📖 Philosophers
</h1>

<p align="center">
	<b><i>Solving The Philosophers Problem</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/isaad18/42-philosophers?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/isaad18/42-philosophers?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/isaad18/42-philosophers?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/isaad18/42-philosophers?color=green" />
</p>



## Description

#### This project is about solving the philosophers problem who sits all together on a round table and have two forks, one on the right and one on the left, as the number of the forks is the same as the number of philosophers. In addition to that, each philosopher needs to eat with two forks so while some philosophers are eating, the others will be waiting them to finish so they can use the forks. As a result, I used threads to be able to run multiple philosophers as processes so they can all go through different tasks to do at the same time, and mutexes as forks to be able to lock them and protect the values from data races.



## QuickStart

### Makefile is provided, you can execute all files using the following command
```
make all
```

### then execute the program with arguements as follows
```
./philo [Number Of Philosophers] [Time To Die] [Time To Eat] [Time To Sleep] [Number Of Arguements]
```
- dfghg
