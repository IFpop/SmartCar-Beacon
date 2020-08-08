/*
 * Kalman_Filters.c
 *
 *  Created on: 8 Aug 2020
 *      Author: BenmuYu0
 */

#include "include.h"

Event_kalman X;
float32 Kalman_Filters(float32* Z){

	float x = X.x;                         //��ô������⵽��x,y,z,Seta,w�������
	float y = X.y;
	float v = X.v;
	float Seta = X.Seta;                   //�Ƕȣ����ǻ���
	float w = X.Seta;

	float x_p 	 = X_update_last[0];     //Ja�ſ˱Ⱦ���������һ��Ԥ��ֵ�����Ի�������ȡֵΪ��һ��������Ԥ��ֵ
	float y_p 	 = X_update_last[1];
	float v_p 	 = X_update_last[2];
	float Seta_p = X_update_last[3];
	float w_p 	 = X_update_last[4];

	/*******************�������Э��������******************/

	if (w<1 && w>-1) 			 				//���ǵ����ٶ�w С��һ��ֵ���϶�Ϊ0
	{
		State_X[0][0] = v * cos(Seta)* dt + x;		//��ǰX��״̬ת����������
		State_X[1][0] = v * sin(Seta)* dt + y;
		State_X[2][0] = v;
		State_X[3][0] = w * dt + Seta;
		State_X[4][0] = w;
        /*StateT_X = {{v*cos(Seta)*dt+ x},
                    {v*sin(Seta)*dt + y},
                    {v},
                    {w*dt + Seta},
                    {w}			        }*/
	}
	else
	{
		State_X[0][0] = v/w*sin(w*dt+Seta)-v/w*sin(Seta)+ X_real[0,i];
		State_X[1][0] = v * sin(Seta)* dt + y;
		State_X[2][0] = v;
		State_X[3][0] = w * dt + Seta;
		State_X[4][0] = w;

		/*StateT_X[:,i] = np.mat([[v/w*sin(w*dt+Seta)-v/w*sin(Seta)+ X_real[0,i]],
                                 [-v/w*cos(w*dt+Seta) + v/w*cos(Seta) + X_real[1,i]],
                                 [v],
                                 [w*dt + Seta],
                                 [w]])										*/
	}

	if(w_p<1 && w_p>-1){

		Ja[0][0] = 1; 	J[0][2] = dt*cos(Seta_p);   J[0][3] = -dt*v_p*sin(Seta_p);       //Ja����
		Ja[1][1] = 1;   J[1][2] = dt*sin(Seta_p);   J[1][3] = dt*v_p*cos(Seta_p);
		Ja[2][2] = 1;
		Ja[3][3] = 1;   Ja[3][4] = dt;
		Ja[4][4] = 1;
        /*Ja = np.mat([[1,0, dt*cos(Seta), -dt*v*sin(Seta), 0],
                  	  [0,1, dt*sin(Seta), dt*v*cos(Seta),  0],
                      [0,0,     1,           0,        	   0],
                      [0,0,     0,           1,       	   dt],
                      [0,0,     0,           0,        	   1]])				*/
	}
	else{

		Ja[0][0] = 1;   										  Ja[0][2] = (1/w_p)*(-sin(Seta_p)+sin(dt*w_p+Seta_p));
		Ja[0][3] = (v_p/w_p)*(-cos(Seta_p)+cos(dt*w_p+Seta_p));   Ja[0][4] = (dt*v_p/w_p)* cos(dt*w_p+Seta_p)-(v_p/w_p^2)*(-sin(Seta_p)+sin(dt*w_p+Seta_p));

		Ja[1][1] = 1;   										  Ja[1][2] = (v_p/w_p)*(-sin(Seta_p)+sin(dt*w_p+Seta_p));
		Ja[1][3] = (1/w_p)*(cos(Seta_p)-cos(dt*w_p+Seta_p));	  Ja[1][4] = (dt*v_p/w_p)*sin(dt*w_p+Seta_p)-(v_p/w_p^2)*(cos(Seta_p)-cos(dt*w_p+Seta_p));

		Ja[2][2] = 1;
		Ja[3][3] = 1;	Ja[3][4] = dt;
		Ja[4][4] = 1;

		/*Ja = np.mat([[1,0,  (1/w_p)*(-sin(Seta_p)+sin(dt*w_p+Seta_p)),   (v_p/w_p)*(-cos(Seta_p)+cos(dt*w_p+Seta_p)),   (dt*v_p/w_p)*cos(dt*w_p+Seta_p)-(v_p/w_p^2)*(-sin(Seta_p)+sin(dt*w_p+Seta_p))],
                       [0,1,  (v_p/w_p)*(-sin(Seta_p)+sin(dt*w_p+Seta_p)), (1/w_p)*(cos(Seta_p)-cos(dt*w_p+Seta_p)),      (dt*v_p/w_p)*sin(dt*w_p+Seta_p)-(v_p/w_p^2)*(cos(Seta_p)-cos(dt*w_p+Seta_p))],
                       [0,0,              1                  ,                           0              ,                     									0                                     ],
                       [0,0,              0                  ,                           1              ,                     									dt                                    ],
                       [0,0,              0                  ,                 			 0              ,                     									1                                     ]])
		 */
	}


	Q[0][0] = (0.5* dt^2 *noise_a*cos(Seta))^2;   			Q[0][1] = 0.25* dt^4 * noise_a^2 *sin(Seta)*cos(Seta);   Q[0][2] = 0.5* dt^3 * noise_a^2 * cos(Seta);
	Q[1][0] = 0.25* dt^4 * noise_a^2 *sin(Seta)*cos(Seta);	Q[1][1] = (0.5* dt^2 *noise_a*sin(Seta))^2;				 Q[1][2] = 0.5* dt^3 * noise_a^2 * sin(Seta);
	Q[2][0] = 0.5* dt^3 * noise_a^2 * cos(Seta);			Q[2][1] = 0.5* dt^3 * noise_a^2 * sin(Seta);			 Q[2][2] = dt^2 * noise_a^2;
	Q[3][3] = (0.5* dt^2 * noise_yaw)^2;					Q[3][4] = 0.5* dt^3 *noise_yaw^2;
	Q[4][3] = 0.5* dt^3 *noise_yaw^2;						Q[4][4] = dt^2 * noise_yaw;
	/*
	Q = np.mat([[(0.5* dt^2 *noise_a*cos(Seta))^2,             0.25* dt^4 * noise_a^2 *sin(Seta)*cos(Seta),  0.5* dt^3 * noise_a^2 * cos(Seta),   0,                          0                    ],
	            [0.25* dt^4 * noise_a^2 *sin(Seta)*cos(Seta), (0.5* dt^2 *noise_a*sin(Seta))^2,              0.5* dt^3 * noise_a^2 * sin(Seta),   0,                          0                    ],
	            [0.5* dt^3 * noise_a^2 * cos(Seta),            0.5* dt^3 * noise_a^2 * sin(Seta),            dt^2 * noise_a^2                 ,   0,                          0                    ],
	            [0,                                            0,                                            0,                                  (0.5* dt^2 * noise_yaw)^2, 0.5* dt^3 *noise_yaw^2 ],
	            [0,                                            0,                                            0,                                   0.5* dt^3 *noise_yaw^2,    dt^2 * noise_yaw      ]])
	*/

	/********************����Э������������*********************/

	X_predict[0] = State[0][0];        //��õ�ǰԤ��ֵ
	X_predict[1] = State[1][0];
	X_predict[2] = State[2][0];
	X_predict[3] = State[3][0];
	X_predict[4] = State[4][0];

	// ��ù۲�ֵ Z                            ����Hl����Ϊ�ԽǾ������Լ򻯼���
	Z[0][0] = Hl[0][0] * Z[0][0];
	Z[1][0] = Hl[1][1] * Z[1][0];
	Z[2][0] = Hl[2][2] * Z[2][0];
	Z[3][0] = Hl[3][3] * Z[3][0];
	Z[4][0] = Hl[4][4] * Z[4][0];

	// ���㵱ǰЭ����P_predict

	float32 tem1[5][5] = {{0}};
	float32 tem2[5][5] = {{0}};
	float32 tem3[5][5] = {{0}};
	Dot(Ja, P_update_last, tem1, 5,5,5,5);	//����Ja * P_update_last���������tem1
	Transpose(Ja, tem2 ,5,5);           //ת��Ja��  �������tem2
	Dot(tem1, tem2, tem3, 5,5,5,5);    		//����Ja * P_update_last * Ja.T���������tem3
	Mat_Plus(tem3,Q, P_predict,5,5);

	//P_predict = Ja * P_update_last * Ja.T + Q  # Ԥ�� P

	//���㿨��������K
	float32 tem4[5][5] = {{0}};
	float32 tem5[5][5] = {{0}};
	float32 tem6[5][5] = {{0}};
	float32 S[5][5]    = {{0}};
	Dot(Hl, P_predict, tem4, 5,5,5,5);       //����Hl * P_predict   �������tem4
	Transpose(Hl, tem5  ,5,5);           //ת��Hl��  �������tem5
	Dot(tem4, tem5, tem6 ,5, 5,5,5);         //����Hl * P_predict* Hl.T�� �������tem6
	Mat_Plus(tem6, R, S,5,5);			 //����S = Hl * P_predict* Hl.T + R�� �������S

	float32 tem7[5][5] = {{0}};
	Dot(P_predict, tem5,tem7,5,5,5,5);       //����P_predict * Hl.T���������tem7
	Diag_Inverse(S, S);                  //����S�棬����S
	Dot(tem7, S, K, 5,5, 5);                //����(P_predict * Hl.T) * np.linalg.inv(S)���������K

	//S = Hl * P_predict* Hl.T + R
	//K = (P_predict * Hl.T) * np.linalg.inv(S)

	//����X_update
	float32 Y[5] = 	 {0};
	float32 tem8[5][5] = {0};
	float32 tem9[5]    = {0};
	Dot(Hl,X_predict, tem8, 5,5, 5,1);      //����Hl* X_predict[:, i]�� ����tem8
	Mat_Sub(Z, tem8, Y,5,1);			    //����Z[:,i+1] - Hl* X_predict[:, i]������Y

	Dot(K,Y, tem9, 5,5, 5,1);				//����(K * y)   ����tem9
	Mat_Plus(X_predict, tem9, X_update, 5,1);//����X_predict[:, i+1] + (K * y)   �������X_update
	//y = Z[:,i+1] - Hl* X_predict[:, i]  # Innovation or Residual   ��Ϣ
	//X_update[:,i+1] = X_predict[:, i+1] + (K * y)


	//����P_update
	float32 tem10[5][5] = {0};
	float32 tem11[5][5] = {0};

	Dot(K,Hl, tem10,5,5,5,5);					//����K * Hl  �������tem10
	Dot(tem10, P_predict, tem11, 5,5,5,5);		//����K * Hl * P_predict   �������tem11
	Mat_Sub(P_predict, tem11, P_update, 5,5);   //����P_predict - K * Hl * P_predict   �������P_update

    //P_update = P_predict - K * Hl * P_predict


	//��һ�μ����P Ϊ��һ�ε�P_last
	int m,n;
	for(m=0;m<5;m++)
	{
		for(n=0;n<5;n++){
		P_predict_last[m][n] = P_predict[m][n];
		}
	}

	for(m=0;m<5;m++)
	{
		for(n=0;n<5;n++){
			P_update_last[m][n] = P_update[m][n];
		}
	}
    //P_predict_last = P_predict
    //P_update_last = P_update

	return *Z;
}



 float32* Transpose(float32 *T, *results,int row, int col){

	int i, j;
//	int i, j, len_row,len_col;
//	len_col = sizeof(T[0])/sizeof(int);
//	len_row = sizeof(T)/sizeof(int)/len_col;

	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			T_T[j][i] = T[i][j];
		}
	}
	return *results;
}

float32* Diag_Inverse(float32 *D, *results){
	int i, j;

	len_n = sizeof(D[0])/sizeof(float);
	len_row = sizeof(D)/sizeof(float)/len_n;
	if(len_n != len_row){                      //ȷ���Ƿ�Ϊ����
		fprintf("Invalid Calculation");
		exit(EXIT_FAILURE);
	}

	else
	{
		for(i=0;i<len_n;i++){
			results[i][i] = 1/D[i][i];
		}
		return *results;
	}
}

float32* Dot(float32 *Mat1, float32 *Mat2,float32 *results,int row1,  int col1,int row2,  int col2)
{
    int i,j,k;

   if(col1!=row2){
       fprintf(stderr,"Input error!");
        exit(EXIT_FAILURE);
   }

   for(i=0;i<row1;i++){
      for(j=0;j<col2;j++){
           for(k=0;k<col1;k++){
        	   results[i][j]=results[i][j]+Mat1[i][k]*Mat2[k][j];
           }
       }
   }
	return *results;
}

float32* Mat_Plus(float32 *K, float32 *I, float32 *results, int row, int col){
	int i,j;
	for(i = 0; i<row; i++){
		for(j = 0; j<col; j++){
		results[i][j] = K[i][j] + I[i][j];
		}
	}
	return *results;
}

float32* Mat_Sub(float32 *K, float32 *I, float32 *results, int row, int col){
	int i,j;
	for(i = 0; i<row; i++){
		for(j = 0; j<col; j++){
		results[i][j] = K[i][j] - I[i][j];
		}
	}
	return *results;
}

