#ifndef GA1_H
#define GA1_H
#include <vector>
using namespace std;

class chromo
{
public:
	vector<short int> bits;
	vector<double> dec_value;            //decimal code of chromo
	double copy_times;         //copy times
	double fitness;          //fitness
    double rate_fit;          //relative fitness
	double cumu_fit;         //cumulative fitness
	double x_max,x_min;
	int chromo_nums_total;  //chromosome numbers
	int popu_nums_total;  //population numbers
	void get_binary_value();   //change the binary code to the decimal code
private:
};

class GA
//class GA, which is the main realization of GA
{
	public:
		GA(int init_chromo_nums = 0, int init_individual_nums = 0 , int init_popu_nums = 0,
			double init_rate_crossover = 0,double init_rate_mutation = 0 , int init_iteration_num = 0,
			double xinx_max = 0 , double xinx_min = 0){
			chromo_nums = init_chromo_nums;
			individual_nums = init_individual_nums;
			popu_nums = init_popu_nums;
			rate_crossover = init_rate_crossover;
			rate_mutation = init_rate_mutation;
			iteration_num = init_iteration_num;
			xin_max = xinx_max;
			xin_min = xinx_min;
			iteration_times = 0;
			best_individual.fitness = INT_MIN;
		}
		double (*fitness_function)(double x,double y);   //fitness function: can be described outside the class
		vector<chromo> chromosome;
		vector<chromo> next_chromosome;
		chromo best_individual;
		chromo *one_chromosome;
	    void population_initialize(); //initialize the chromosome
		void iteration_procedure();   //the procedure of iteration
 	private:
		unsigned int iteration_times ; 
		double xin_max,xin_min;   //The excursion of the input number
		int chromo_nums;  //chromosome numbers
		int individual_nums; //individual numbers
		int popu_nums;  //population numbers
		double rate_crossover;  //crossover rate
		double rate_mutation;   //mutation rate
		int iteration_num;    //iteration times
		void fresh_property();         //refresh each indivdual in the population
		void select_individual();      //select the individual in the population using roulette selection method
		void crossover();             //the crossover operation
		void mutation();             //the mutation operation
		void iteration_once();
		void compute_next_fitness();
		void get_best_individual();
		void calcu_cumurate(vector<chromo> *chromosome);
};

#endif