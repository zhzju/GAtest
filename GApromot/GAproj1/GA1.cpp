#include "stdafx.h"

void GA::population_initialize()
{
	srand(iteration_times + (unsigned)time(NULL));
	 for (int j = 0; j<individual_nums; j++)                              
    {
		one_chromosome = new chromo;
		cout<<"No"<<j<<":";
        //initialize each bit of the chromosome randomly
		for (int i = 0; i<chromo_nums*popu_nums; i++)                       
        {
			//series different population into one sequence
			one_chromosome->bits.push_back(rand()% 2);
			cout<<one_chromosome->bits[i];
        }
		cout<<endl;
		chromosome.push_back(*one_chromosome);
		delete one_chromosome;
    }
}


void GA::select_individual()
{
	srand(iteration_times + (unsigned)time(NULL));
	double rate_rand = 0.0;
	for(int i = 0 ; i < individual_nums ; i++)
	{
		rate_rand = ((double)rand())/(RAND_MAX);
		if (rate_rand < chromosome[0].cumu_fit)
			next_chromosome.push_back(chromosome[0]); 
		 else
        {for (int j = 0; j < individual_nums; j++){
			if(j == individual_nums -1 )
			{
				next_chromosome.push_back(chromosome[j]);break;
			}
          if (chromosome[j].cumu_fit <= rate_rand && rate_rand < chromosome[j + 1].cumu_fit)
          {next_chromosome.push_back(chromosome[j + 1]);
                  break;}}}
	}
	//cout<<" selectok"<<next_chromosome.size()<<" ";
}


void GA::crossover()
{

	srand(iteration_times + (unsigned)time(NULL));
	double chaos_initial = ((double)rand())/(RAND_MAX);
	double chaos_para = chaos_initial;
	vector<int> chaos_sequence;
	short int bit_temp = 0;
			//cout<<" crossoverstart1 ";
	//vector<int> sequence_mid;  //generate sequence randomly

	//pair randomly
	//int num_mid;
	//while(sequence_mid.size()<individual_nums)
	//{
	//	num_mid = rand()%individual_nums;
	//	vector<int>::iterator result = find( sequence_mid.begin( ), sequence_mid.end( ), num_mid ); 
	//	if ( result == sequence_mid.end( ) ) {sequence_mid.push_back(num_mid);} 
	//}

	//optimal pairing
	//bubble sort
	chromo temp;
	for(int i=0 ; i < individual_nums - 1; i++)
		for(int j = 0 ; j < individual_nums - 1 - i ; j++)
			if(next_chromosome[j].fitness < next_chromosome[j+1].fitness)
			{
				temp = next_chromosome[j];
				next_chromosome[j] = next_chromosome[j+1];
				next_chromosome[j+1]= temp;
			}
		//cout<<" crossoverstart2 ";
	vector<chromo> next_chromosome_mid = next_chromosome;
	next_chromosome.clear();
	double rate_rand = 0;
	chromo chromo_mid1;
	chromo chromo_mid2;
			//cout<<" crossoverstart3 ";
	while(next_chromosome_mid.size() != 0)
	{
		int number_need = 0;
		rate_rand = ((double)rand())/(RAND_MAX);
		chromo_mid1 = next_chromosome_mid[0];
		next_chromosome_mid.erase(next_chromosome_mid.begin());
		calcu_cumurate(&next_chromosome_mid);
		if (rate_rand < next_chromosome_mid[0].cumu_fit)
			number_need = 0; 
		 else
		 {for (int j = 0; j < next_chromosome_mid.size(); j++){
			 if(j == next_chromosome_mid.size() -1 )
			{
				number_need = j;break;
			}
          if (next_chromosome_mid[j].cumu_fit <= rate_rand && rate_rand < next_chromosome_mid[j + 1].cumu_fit)
          {number_need = j+1;
                  break;}}}
		chromo_mid2 = next_chromosome_mid[number_need];
		next_chromosome_mid.erase(next_chromosome_mid.begin()+number_need);

		//get two individual 0 and number_need, then imply crossover algorithm
		//crossover algorithm using logisticd chatic sequences
		int cross_len = (int)rand()%(chromo_nums*popu_nums);  //generate the cross length
		if(cross_len > chromo_nums*popu_nums) cross_len = chromo_nums*popu_nums;
		chaos_sequence.clear();
		chaos_sequence.push_back((int)(chaos_initial*chromo_nums*popu_nums));

		for(int j = 0; j< cross_len-1;j++)
		{
			chaos_para = 4*chaos_para*(1.0 -chaos_para);
			chaos_sequence.push_back((int)(chaos_para*chromo_nums*popu_nums));
		}
		double rate_randm = ((double)rand())/(RAND_MAX);
		if(rate_randm <= rate_crossover)
		for(int j = 0; j< chaos_sequence.size(); j++)
		{
		bit_temp = chromo_mid1.bits[chaos_sequence[j]];
		chromo_mid1.bits[chaos_sequence[j]] = chromo_mid2.bits[chaos_sequence[j]];
		chromo_mid2.bits[chaos_sequence[j]] = bit_temp;
		}
		next_chromosome.push_back(chromo_mid1);
		next_chromosome.push_back(chromo_mid2);
	}
	//cout<<" crossoverok ";
	//double rate_rand = 0.0;
	//int position_rand = 0;
	//
	//for(int j = 0;j<individual_nums/2; j++)
	//{
	//	rate_rand = (float)rand()/(RAND_MAX);
	//	 if(rate_rand <= rate_crossover)
	//	 {
	//		 position_rand = (int)rand()%(chromo_nums*popu_nums); //crossover position
	//		 for( int  i = position_rand; i <chromo_nums*popu_nums ; i++)
	//		 {
	//			 bit_temp = next_chromosome[sequence_mid[j]].bits[i];
	//			 next_chromosome[sequence_mid[j]].bits[i] = next_chromosome[sequence_mid[individual_nums/2+j]].bits[i];
	//			 next_chromosome[sequence_mid[j+individual_nums/2]].bits[i] = bit_temp;
	//		 }
	//	 }
	//}
}

void GA::mutation()
{
	//big mutation operation and normal mutation operation
	//bubble sort
	chromo temp;
	for(int i=0 ; i < individual_nums - 1; i++)
		for(int j = 0 ; j < individual_nums - 1 - i ; j++)
			if(next_chromosome[j].fitness < next_chromosome[j+1].fitness)
			{
				temp = next_chromosome[j];
				next_chromosome[j] = next_chromosome[j+1];
				next_chromosome[j+1]= temp;
			}
	srand(iteration_times + (unsigned)time(NULL));
	double rate_rand = 0.0;
	int position_rand = 0;
	if(0.8 * next_chromosome[0].cumu_fit > 1.0/next_chromosome.size()){
	for(int j = 0;j<individual_nums; j++)  //mutation times equals to individual numbers 
	{
		rate_rand = ((double)rand())/(RAND_MAX);
		if(rate_rand <= rate_mutation)
		 {
			 position_rand = (int)rand()%(chromo_nums*popu_nums);
			 next_chromosome[j].bits[position_rand] = 1 - next_chromosome[j].bits[position_rand];
		 }
	}}
	else  //big mutation operation
	{
	for(int j = 1;j<individual_nums; j++) 
	{
		next_chromosome[j] = next_chromosome[0];
	}
	for(int j = 0;j<individual_nums; j++)  //mutation times equals to individual numbers 
	{
		rate_rand = (float)rand()/(RAND_MAX);
		if(rate_rand <= rate_mutation * 10)
		 {
			 position_rand = (int)rand()%(chromo_nums*popu_nums);
			 next_chromosome[j].bits[position_rand] = 1 - next_chromosome[j].bits[position_rand];
		 }
	}
	}
		//cout<<" mutationok ";
}

void GA::fresh_property()
{
calcu_cumurate(&chromosome);
		//cout<<" freshok ";
}

void GA::compute_next_fitness()
{
calcu_cumurate(&next_chromosome);
		//cout<<" computeok ";
}

void GA::iteration_once()
{
	double ave_fitness_next = 0;
	double ave_fitness_now = 0;
	double max_fitness = 0;
	fresh_property();
	select_individual();
	compute_next_fitness();
	crossover();
	mutation();
	compute_next_fitness();
	for(int j = 0 ; j < chromosome.size() ; j++)
	{ave_fitness_now += chromosome[j].fitness;
	ave_fitness_next += next_chromosome[j].fitness;
	}
	ave_fitness_now = ave_fitness_now / chromosome.size();
	ave_fitness_next = ave_fitness_next / chromosome.size();
	//if(ave_fitness_next >  ave_fitness_now){
	for(int j = 0 ; j < chromosome.size() ; j++)
	{
		chromosome[j] = next_chromosome[j];
	}//}
	cout<<" fitness average:"<<ave_fitness_next;
	next_chromosome.clear();
	int mem_max = 0;
	for(int j = 0 ; j < chromosome.size() ; j++)
	{
		if(max_fitness < chromosome[j].fitness)
		{
			max_fitness = chromosome[j].fitness;
			mem_max = j;
		}
	}
	cout<<" x_max:"<<chromosome[mem_max].dec_value[0]<<" "<<"y_max:"<<chromosome[mem_max].dec_value[1]<<endl;
	get_best_individual();
}


void GA::iteration_procedure()
{
	for(; iteration_times <= iteration_num ; iteration_times++)
	{
		cout<<"iteration times:"<<iteration_times;
		iteration_once();
	}
	cout<<endl;
	cout<<"the best individual is: x_max:"<<best_individual.dec_value[0]<<" y_max: "<<best_individual.dec_value[1]<<endl;
	cout<<"the optimal value of the fitness function is : " <<best_individual.fitness<<endl;
}


void GA::get_best_individual()
{
	double best_fit = 0;
	int best_num = 0;
	for(int j = 0 ; j < chromosome.size() ; j++)
	{
		if(chromosome[j].fitness > best_fit)
		{best_fit = chromosome[j].fitness;best_num = j;}
	}
	if(chromosome[best_num].fitness >best_individual.fitness)
		best_individual = chromosome[best_num];

}

void chromo::get_binary_value()
{
	double current_value = 0.0;
	chromo_nums_total = bits.size()/popu_nums_total;
	for(int i = 0 ; i < popu_nums_total; i++)
	{
		current_value = 0;
		for(int j = i*chromo_nums_total ; j < (i+1)*chromo_nums_total;j++)
		{
			current_value += bits[j]*pow(2,chromo_nums_total*(i+1)-j-1);
		}
		current_value = x_min + current_value/(pow(2,chromo_nums_total)-1.0)*(x_max - x_min);
		current_value = (int)(current_value*10000+0.5)/10000.0; //keep the four decimal places
		//cout<<current_value<<" ";
		dec_value.push_back(current_value);
	}
	//cout<<endl;
}


void GA::calcu_cumurate(vector<chromo> *chromosome)
{
	double sum = 0;
	for(int j = 0;j<(*chromosome).size(); j++)
	{
		(*chromosome)[j].copy_times = 0;
		(*chromosome)[j].dec_value.clear();
		(*chromosome)[j].x_max = xin_max;
		(*chromosome)[j].x_min = xin_min;
		(*chromosome)[j].popu_nums_total = popu_nums;
		(*chromosome)[j].get_binary_value();
		if(fitness_function != NULL)
			(*chromosome)[j].fitness = fitness_function((*chromosome)[j].dec_value[0],(*chromosome)[j].dec_value[1]); //Only when the number of input is two
		else {cout<<"Error";break;}
		sum += (*chromosome)[j].fitness;
	}
	vector<double> fit_cumu;
	for(int j = 0 ; j < (*chromosome).size() ; j++)
	{
	fit_cumu.push_back((*chromosome)[j].fitness);
	}
	std::vector<double>::iterator min = min_element(std::begin(fit_cumu), std::end(fit_cumu));
	if(*min < 0){
	sum = 0;
	for (int j = 0 ; j < (*chromosome).size(); j++)
	{
		fit_cumu[j] = (fit_cumu[j]- *min);
		sum += fit_cumu[j];
	}
	for (int j = 0 ; j < (*chromosome).size(); j++)
	{
		(*chromosome)[j].rate_fit = (fit_cumu[j]) / sum;
	}
	}
	else
	for (int j = 0 ; j < (*chromosome).size(); j++)
	{
		(*chromosome)[j].rate_fit = ((*chromosome)[j].fitness) / sum;
	}

	(*chromosome)[0].cumu_fit = (*chromosome)[0].rate_fit;
	for(int j = 1; j < (*chromosome).size();j++)
	{
		(*chromosome)[j].cumu_fit = (*chromosome)[j].rate_fit + (*chromosome)[j-1].cumu_fit;
	}
}

