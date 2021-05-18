#include <iostream>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include <math.h>
#define s1 inputstring1
#define s3 inputstring2
#define rows  100
#define coloumns 100
using namespace std;

void zero_intializtion(float input[rows][coloumns]);

void string_to_double(string s1, float input1[rows][coloumns], int& j, int& count);

void sum_operation(float input1[rows][coloumns], float input2[rows][coloumns], float total[rows][coloumns]);

void sub_operation(float input1[rows][coloumns], float input2[rows][coloumns], float total[rows][coloumns]);

void multiply_operation(float input1[rows][coloumns], float input2[rows][coloumns], float total[rows][coloumns], int actual_rows1, int actual_coloumns1, int actual_rows2, int actual_coloumns2);

void printing_results(float total[rows][coloumns], int actual_rows1, int actual_coloumns1, int actual_coloumns2, int operation);

void copy_operation(float input1[rows][coloumns], float input2[rows][coloumns], int actual_rows1, int actual_coloumns1);

void power_operation(float input1[rows][coloumns], float total[rows][coloumns], int order, int actual_rows1, int actual_coloumns1);

float determinant(float input1[rows][coloumns], float total[rows][coloumns],int actual_rows1, int actual_coloumns1);


void transpose(float input1[rows][coloumns], float total[rows][coloumns], int actual_rows1, int actual_coloumns1);



float inverse(float input1[rows][coloumns], float total[rows][coloumns], int actual_rows1, int actual_coloumns1);


void divide(float input1[rows][coloumns], float input2[rows][coloumns], float total[rows][coloumns], int actual_rows1, int actual_coloumns1, int actual_rows2, int actual_coloumns2)
{

	inverse(input2, total, actual_coloumns1, actual_rows1);

	zero_intializtion(total);


	if((actual_rows1 == actual_rows2 && actual_coloumns1 == actual_coloumns2 ) || actual_coloumns1 == actual_rows2)

	multiply_operation(input1,input2, total, actual_rows1, actual_coloumns1 , actual_rows2 , actual_coloumns2);
	else
	{
		cout << "ERROR" << endl;
		exit(0);
	}



}






float input1[rows][coloumns];

int main() {

	float input1[rows][coloumns];
	zero_intializtion(input1);
	string s1;
	int count = 0; //number of coloumns  
	int j = 0;      //number of rows
	getline(cin, s1);

	string_to_double(s1, input1, j, count);

	//input 1 is ready to be used
	//determine actual rows and coloumns for the first input
	int actual_rows1 = j + 1;
	int actual_coloumns1 = count;



	int actual_rows2;
	int actual_coloumns2;
	// getting operation
	char operation;
	cin >> operation;


	float total[rows][coloumns];
	zero_intializtion(total);


	if (operation == '+' || operation == '-' || operation == '*')
	{
		//empty line
		string empty;
		getline(cin, empty);

		//getting input2
		float input2[rows][coloumns];
		zero_intializtion(input2);
		string s3;
		getline(cin, s3);

		string_to_double(s3, input2, j, count);
		//determine actual rows and coloumns for the second input
		actual_rows2 = j + 1;
		actual_coloumns2 = count;

		//input 2 is ready to be used

		if (actual_rows1 == actual_rows2 && actual_coloumns1 == actual_coloumns2) // inputs are in the same order + - * are valid 
		{
			switch (operation)
			{
			case '+':
				sum_operation(input1, input2, total);
				printing_results(total, actual_rows1, actual_coloumns1, actual_coloumns2, operation);
				break;
			case '-':
				sub_operation(input1, input2, total);
				printing_results(total, actual_rows1, actual_coloumns1, actual_coloumns2, operation);
				break;
			case '*':
				multiply_operation(input1, input2, total, actual_rows1, actual_coloumns1, actual_rows2, actual_coloumns2);
				printing_results(total, actual_rows1, actual_coloumns1, actual_coloumns2, operation);
				break;
			default:
				cout << "ERROR" << endl;
				break;
			}

		}
		else if (actual_coloumns1 == actual_rows2)
		{
			switch (operation)
			{
			case '*':
				multiply_operation(input1, input2, total, actual_rows1, actual_coloumns1, actual_rows2, actual_coloumns2);
				printing_results(total, actual_rows1, actual_coloumns1, actual_coloumns2, operation);
				break;
			default:
				cout << "ERROR" << endl;
				break;
			}
		}
		else   cout << "ERROR" << endl;


	}
	else if (operation == '^' || operation == 'T' || operation == 'D')
	{
		// level 2
		int order;
		if (operation == '^')
		{
			cin >> order;
		}
		if (actual_rows1 == actual_coloumns1) //square matrix ^  & D are valid
		{
			switch (operation)
			{
			case '^':
				power_operation(input1, total, order, actual_rows1, actual_coloumns1);
				printing_results(total, actual_rows1, actual_coloumns1, 0, operation);
				break;
			case 'D':
				cout << determinant(input1,total ,actual_rows1, actual_coloumns1);
				break;
			case 'T':
				transpose(input1, total, actual_rows1, actual_coloumns1);
				printing_results(total, actual_rows1, actual_coloumns1, 0, operation);
				break;

			default:  break;

			}
		}
		else if (actual_rows1 != actual_coloumns1)
		{
			switch (operation)
			{
			case'T':
				transpose(input1, total, actual_rows1, actual_coloumns1);
				printing_results(total, actual_rows1, actual_coloumns1, 0, operation);
				break;
			default:
				cout << "ERROR" << endl;
				break;

			}

		}
		else
		{
			cout << "ERROR" << endl;

		}

	}
	else if (operation == 'I' || operation == '/')
	{
		// level 3
		if (actual_rows1 == actual_coloumns1)		  //square matrix 
		{
			switch (operation)
			{
			case 'I'  :
				inverse(input1,total, actual_rows1, actual_coloumns1);
				printing_results(input1, actual_rows1, actual_coloumns1, 0, operation);
				break;
			case'/':
			{
				//empty line
				string empty ;
				getline(cin, empty);

				//getting input2
				float input2[rows][coloumns];
				zero_intializtion(input2);
				string s3;
				getline(cin, s3);

				string_to_double(s3, input2, j, count);
				//determine actual rows and coloumns for the second input
				actual_rows2 = j + 1;
				actual_coloumns2 = count;


				divide(input1, input2, total, actual_rows1, actual_coloumns1, actual_rows2, actual_coloumns2);

				printing_results(total, actual_rows1, actual_coloumns1, 0, operation);


				break;
			}
			default:
				break;
			}



		}
		else if (actual_rows1 != actual_coloumns1)
		{
	       
			switch (operation)
			{
			case'/':
			{
				//empty line
				string empty = "";
				getline(cin, empty);

				//getting input2
				float input2[rows][coloumns];
				zero_intializtion(input2);
				string s3;
				getline(cin, s3);

				string_to_double(s3, input2, j, count);
				//determine actual rows and coloumns for the second input
				actual_rows2 = j + 1;
				actual_coloumns2 = count;


				if (actual_coloumns1 != actual_rows2) {
					cout << "ERROR" << endl;
					return 0; 
				}
				divide(input1, input2, total, actual_rows1, actual_coloumns1, actual_rows2, actual_coloumns2);

				printing_results(total, actual_rows1, actual_coloumns1, 0, operation);


				break;
			}
			default:
				cout << "ERROR" << endl;
				break;
			}
		}
		else
		{
			cout << "ERROR" << endl;
		}





	}
	else cout << "ERROR" << endl;



	return 0;
}





















/************************************************************************************************************************************************************

								  Functions
***************************************************************************************************************************************************************/

void zero_intializtion(float input[rows][coloumns])
{

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < coloumns; j++)
		{
			input[i][j] = 0;
		}
	}
}
void copy_operation(float input1[rows][coloumns], float input2[rows][coloumns], int actual_rows1, int actual_coloumns1) {

	for (int j = 0; j < actual_rows1; j++)
	{
		for (int k = 0; k < actual_coloumns1; k++)
		{

			input1[j][k] = input2[j][k];

		}
	}

}

void string_to_double(string s1, float input1[rows][coloumns], int& j, int& count)
{
	string s2; // string to store the string value of the string initially is empty
	float v; //variable to store intger values of strings
	string real_complex;
	string imag_complex;
	int i = 0;

	for (j = 0; j < s1.size(); j++) // bt3ady 3la kol el string 34an t7dd el rows 
	{
		int flag1 = 0; //flag to stop adding strings togther
		int col_check = count;
		count = 0;
		for (i; i < s1.size(); i++)// bt3ady 3la kol el string 34an t7dd el coloums
		{
			if (s1[i] == ' ' && s1[i + 1] == ' ') //Erorr for missing values 
			{
				cout << "ERROR" << endl;
				exit(0);
			}
			if (s1[i] != '[' && s1[i] != ']' && s1[i] != ' ' && s1[i] != ';' && s1[i] != 'i')
			{
				//so s1[i] is a number
				s2 += s1[i]; //add strings togther  

				if (s1[i + 1] == ' ') //if string ended we must convert the currnt string into nubmer
				{
					flag1 = 1;
				}
				else if (s1[i + 1] == ';')
				{
					flag1 = 1;
					break;
				}
				else if (s1[i + 1] == ']') {
					flag1 = 2;
					break;
				}


				if (flag1 == 1) //converting string into number
				{
					v = atof(s2.c_str());
					input1[j][count] = v;
					count++;
					flag1 = 0;
					s2 = ""; //emptying string 
				}

			}
			else if
				(s1[i] == ']') break;
		}
		if (flag1 == 1) //converting string into number
		{
			v = atof(s2.c_str());
			input1[j][count] = v;
			count++;
			s2 = ""; //emptying string 
			i++;
		}
		else if (flag1 == 2)
		{
			//if s2=19.20 -> v1=19.19999999999993 why????
			v = atof(s2.c_str());
			input1[j][count] = v;
			count++;
			s2 = ""; //emptying string 
			if (col_check != count && j > 0)
			{
				cout << "ERROR" << endl;
				exit(0);
			}
			break; // break from the bigger loop

		}
	}
}
void sum_operation(float input1[rows][coloumns], float input2[rows][coloumns], float total[rows][coloumns])
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < coloumns; j++)
		{
			total[i][j] = input1[i][j] + input2[i][j];
		}
	}
}
void sub_operation(float input1[rows][coloumns], float input2[rows][coloumns], float total[rows][coloumns])
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < coloumns; j++)
		{
			total[i][j] = input1[i][j] - input2[i][j];
		}
	}
}
void multiply_operation(float input1[rows][coloumns], float input2[rows][coloumns], float total[rows][coloumns], int actual_rows1, int actual_coloumns1, int actual_rows2, int actual_coloumns2)
{
	for (int i = 0; i < actual_rows1; ++i)
	{
		for (int j = 0; j < actual_coloumns2; ++j)
			for (int k = 0; k < actual_coloumns1; ++k)
			{
				total[i][j] += input1[i][k] * input2[k][j];
			}
	}
}
void power_operation(float input1[rows][coloumns], float total[rows][coloumns], int order, int actual_rows1, int actual_coloumns1)
{
	float temp[rows][coloumns];
	zero_intializtion(temp);
	int actual_rows2 = actual_rows1;
	int actual_coloumns2 = actual_coloumns1;
	//we need to make total = input1

	copy_operation(temp, input1, actual_rows1, actual_coloumns1);

	//multiply total * input1 and assign the result in total 
	for (int i = 1; i < order; i++) {
		zero_intializtion(total);
		multiply_operation(temp, input1, total, actual_rows1, actual_coloumns1, actual_rows2, actual_coloumns2);
		copy_operation(temp, total, actual_rows1, actual_coloumns1);
	}
}
void printing_results(float total[rows][coloumns], int actual_rows1, int actual_coloumns1, int actual_coloumns2, int operation)
{
	int row = 0;
	int col = 0;
	switch (operation)
	{
	case '+':
	case '-':
	case '^':
	case 'I':
	case '/':
		row = actual_rows1; //inputs are the same 
		col = actual_coloumns1;
	case 'T':
		row = actual_coloumns1;
		col = actual_rows1;
		break;
	case '*':
		row = actual_rows1;//total must be 3 x 1 * 1 x3  =  3 x 3
		col = actual_coloumns2;
		break;
	}
	//printing
	cout << "[";
	for (int j = 0; j <= row - 1; j++)
	{
		for (int i = 0; i <= col - 1; i++)
		{
			if (i == (col - 1))
				cout << total[j][i];
			else
				cout << total[j][i] << " ";
		}
		if (j == (row - 1))
			break;
		else
			cout << ";";
	}
	cout << "]" << endl;
}



float determinant(float input1[rows][coloumns], float total[rows][coloumns] , int actual_rows1, int actual_coloumns1) {

	float temp;
	float result = input1[0][0];

	copy_operation(total, input1, actual_rows1, actual_coloumns1);

	for (int i = 0; i < actual_coloumns1 - 1; i++)
	{   // 3ayz y3ml sofof el awel b3deen el a3meda
		for (int j = 0; j < actual_rows1 - 1; j++)
		{
			int k;
			//we want to make first element zero 
			//step 1  n2sm el value 3ala awel element f el matrix 
			temp = total[j + 1 + i][i] / total[i][i];
			//edit the orginal matrix 
			for (int k = 0; k < actual_coloumns1; k++)
			{
				total[j + 1 + i][k + i] -= (temp * total[i][k + i]);
			}
		}
	}
	for (int i = 1; i < actual_coloumns1; i++)
	{
		result *= total[i][i];

	}
	return result;
}

void transpose(float input1[rows][coloumns], float total[rows][coloumns], int actual_rows1, int actual_coloumns1)
{
	for (int i = 0; i < actual_rows1; i++)
	{
		for (int j = 0; j < actual_coloumns1; j++)
		{
			total[j][i] = input1[i][j];

		}

	}

}


float inverse(float input1[rows][coloumns], float total[rows][coloumns], int actual_rows1, int actual_coloumns1)
{
	float C = determinant(input1, total, actual_rows1, actual_coloumns1);
	if (C == 0)
	{
		cout << "ERROR" << endl;
		exit(0);
	}
	// calculating the adjent of the matrix 
	float inverse[rows][coloumns] = { 0 };
	// getting I matrix 
	for (int i = 0; i < actual_rows1; i++)
	{
		for (int j = 0; j < actual_coloumns1; j++)
		{
			if (i == j)
				inverse[i][j] = 1;
			else inverse[i][j] = 0;
		}
	}

	copy_operation(total, input1, actual_rows1, actual_coloumns1);



	for (int i = 0; i < actual_rows1  ; i++) { 

		for (int j = 0; j < actual_rows1  ; j++) { 
			float temp;
			if (j != i) {

				temp = total[j][i] / total[i][i];
				for (int k = 0; k < actual_coloumns1; k++) {

					total[j][k] -= total[i][k] * temp;
					inverse[j][k] -= inverse[i][k] * temp;

				}
			}
		}
	}


	// tom  get 1 in the diagonal 
	for (int i = 0; i < actual_rows1; i++)
	{

		float a = total[i][i];
		for (int j = 0; j < actual_coloumns1; j++)
		{

			total[i][j] /= a;
			inverse[i][j] /= a;
		}
	}

	/*
	  float temp;
	  for (int i = 0; i < actual_coloumns1 - 1; i++)
	  {   // 3ayz y3ml sofof el awel b3deen el a3meda
		  for (int j = 0; j < actual_rows1 - 1; j++)
		  {
			  //we want to make first element zero
			  //step 1  n2sm el value 3ala awel element f el matrix
			  temp = total[j + 1 + i][i] / total[i][i];
			  //edit the orginal matrix
			  for (int k = 0; k < actual_coloumns1; k++)
			  {
				  total[j + 1 + i][k + i] -= (temp * total[i][k + i]);

				  inverse[j + 1 + i][k + i] -= (temp * inverse[i][k + i]);
			  }
		  }
	  }

	  // keda fe 3 asfar t7t

	// tom  get 1 in the diagonal
	  for (int i = 0; i < actual_rows1; i++)
	  {

		  float a = total[i][i];
		  for (int j = 0; j < actual_coloumns1; j++)
		  {

			  total[i][j] /= a;
			  inverse[i][j] /= a;
		  }
	  }

		 // we want to form upper triangle with zero

	  for (int i = 0; i < actual_rows1 ; i++)
	  {
		  for (int j = 0; j < actual_coloumns1 ; j++)
		  {
			  float b = 0;
			  if (j > i)
			  {
				  b = total[i][j];

				  for (int k = 0; k < actual_coloumns1 ; k++)
				  {
					  total[i][k] -= total[j][k] * b;
					  inverse[i][k] -= inverse[j][k] * b;
				  }
			  }
		  }

	  }

		   */
	copy_operation(input1, inverse, actual_rows1, actual_coloumns1);
}