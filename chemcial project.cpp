#include <stdio.h>
#include<string.h>
#include<math.h>
#define element_num 10 //化学式中的元素种类数
#define length 21 //化学式的长度(length-1)
#define total_element 10 //已录入化学元素数量
struct element
{
    int number;
    char sign[3];
    double atomic_mass;
};

struct element w[total_element] = { {1,"H",1.0079},{2,"He",4.0026},{3,"Li",6.9410},{4,"Be",9.0122},{5,"B",10.811},{6,"C",12.0110},{7,"N",14.0070},{8,"O",15.9990},{9,"F",18.9980},{10,"Ne",20.1700}};

int main()
{
    char sign1[length] = { 0 }, complete_array[element_num][3] = { 0 };//sign1是我们输入的字符（按照平时书写的输入即可）,complete_array是括号外的元素列表
    char jituan[element_num][3] = {0};//jituan是括号内的元素列表状况
    void recognition(char example[], char example2[element_num][3],int numbers1[element_num][1]);
 //待改：   void outputinformation(char example[element_num][3], int numbers1[element_num][1], char example1[element_num][3], int numbers2[element_num][1], int numbers3[1]);
    void caculation(char example1[element_num][3], int numbers[element_num][1],char example2_kuohao[element_num][3], int numbers2_kuohao[element_num][2], int kuohao_out[1]);
    void kuohao_recognition(char examples[], char jituan[element_num][3], int numbers_of_kuohao_in[element_num][2], int numbers_of_kuohao_out[1]);
    int number_of_atom_in_main[element_num][1] = { 0 }, number_of_atom_in_main_kuohao[element_num][2] = { 0 }, kuohao_out[1] = { 0 };//number_of_atom_in_main是括号外的元素的计量数，number_of_atom_in_main_kuohao是括号内的元素计量数，kuohao_out是括号外的计量数
    while (1)
    {
        printf("please input the chemical element > ");
        scanf_s("%s",sign1,length);
        recognition(sign1, complete_array,number_of_atom_in_main);
        kuohao_recognition(sign1, jituan, number_of_atom_in_main_kuohao, kuohao_out);
        caculation(complete_array, number_of_atom_in_main, jituan, number_of_atom_in_main_kuohao,kuohao_out);
//待改：       outputinformation(complete_array,jituan,number_of_atom_in_main_kuohao);
    }
}

void recognition(char example[],char example2[element_num][3],int numbers1[element_num][1])//处理并识别括号外的元素和数字,第一个为导入的字符数组，第二个为输出的整理好的字符数组(可能会有重复的元素名)，第三个为对应好的整理好的输出字符的计量数数组
{
    int b, c, d, weishu = 0,kuohao_weishu=0 ,number_of_atom_in_recognition[element_num][1] = { 0 }, record_of_number[4] = { 0 }, flag = 0;//flag是括号开关器，flag2是检查化学式是否符合我的规定
    char N1[element_num][3] = { 0 };//此函数中存储的整理好的元素的字符数组,N1是没括号的情况
    for (b = 0, c = 0; b < length; b++)//逐个扫描字符，这个循环中b代表字符的水平位置，c代表统计元素的序号（数组设置为竖直方向）
    {
        if (example[b] >= 65 && example[b] <= 87 && flag == 0)//检测大写字符
        {
            if (example[b] >= 65 && example[b] <= 87)
            {
                numbers1[c][0] = 1;//设置元素的初始数量为1(即元素后面不写数字的情况的默认值为1)
                if (example[b + 1] >= 97 && example[b + 1] <= 121)//检测第二个是否是小写字符，是则记录元素名
                {
                    N1[c][0] = example[b];
                    N1[c][1] = example[b + 1];
                }
                else
                    N1[c][0] = example[b];
                c++;
            }
        }
        if (example[b] > 48 && example[b] <= 57 && weishu<=3 && flag ==0)//检测数字,只能有三位整数
        {
            record_of_number[weishu] = example[b] - 48;
            weishu++;
        }
        if (weishu > 0 && c > 0)//检测到新数字的话就开始覆写新数值给前一个元素
        {
            number_of_atom_in_recognition[c - 1][0] = pow(10, weishu - 1) * record_of_number[0] + pow(10, weishu - 2) * record_of_number[1] + pow(10, weishu - 3) * record_of_number[2];
            numbers1[c - 1][0] = number_of_atom_in_recognition[c - 1][0];
            weishu = 0;
            for (d = 0; d < 3; d++)
                record_of_number[d] = 0;
        }
        if (example[b] == 40)//括号开始出的元素不扫描
            flag = 1;//1是关,0是开
        if (example[b] == 41)//括号以及数字结束后可以扫描了，根据数字的数量跳过扫描
        {
            for (d = 1; d <= 3; d++)
            {
                if (example[b + d] > 48 && example[b + d] <= 57)
                    kuohao_weishu++;
                if (example[b + d] >= 65 && example[b + d] <= 87)
                    break;
            }
            flag = 0;
            b += kuohao_weishu;
        }
    }
    for (b = 0; b < element_num; b++)//指针，用于返还整理好的新2维数组，此循环中b代表元素的位置，c为记录元素符号的位置
        for (c = 0; c < 3; c++)
            example2[b][c] = N1[b][c];
}
//输出相关的信息   待重做！！！！
void outputinformation(char example[element_num][3], int numbers1[element_num][1], char example1[element_num][3], int numbers2[element_num][1], int numbers3[1])//参数一：括号外的元素表；参数二：括号外元素的计量数表；参数三：括号内的元素表；参数四：括号内的计量数表；参数五：括号外的数字
{
    char thirdArray[3] = { 0 }, fourthArray[3] = { 0 }, condition[element_num][3] = { 0 };
    int b, c, d, e, f, g, xuhao=0, condition_of_numbers[element_num][1] = { 0 };
    for (b = 0; b < element_num; b++)//先处理括号外面的
    {
        for (c = 0; c < 3; c++)
            thirdArray[c] = example[b][c];
        for (c=0;c<element_num;c++)
            if (strcmp(thirdArray, w[c].sign))
            {
                for (d = 0; d < element_num; d++)
                {
                    for (e = 0; e < 3; e++)
                        fourthArray[e] = condition[d][e];
                    if (strcmp(thirdArray, fourthArray) == 0)
                        condition_of_numbers[d][0] += numbers1[b][0];
                }

            }


    }
}

void caculation(char example1[element_num][3], int numbers[element_num][1],char example2_kuohao[element_num][3], int numbers2_kuohao[element_num][2], int kuohao_out[1])//计算原子序数之和
{
    int a, b, c, sum_of_atoms_numbers_in = 0, sum_of_atoms_numbers_kuohao =0, sum_of_atoms_numbers=0;
    char thirdArray[3] = { 0 };
    for (a = 0; a < element_num; a++)//匹配元素并计算
    {
        for (b = 0; b < 3; b++)
            thirdArray[b] = example1[a][b];
        for(c=0;c< total_element;c++)
            if (strcmp(thirdArray, w[c].sign) == 0)
            {
                sum_of_atoms_numbers_in += w[c].number * numbers[a][0];
                break;
            }
    }
    for (a = 0; a < element_num; a++)
    {
        for (b = 0; b < 3; b++)
            thirdArray[b] = example2_kuohao[a][b];
        for(c=0;c< total_element;c++)
            if (strcmp(thirdArray, w[c].sign) == 0)
            {
                sum_of_atoms_numbers_kuohao += w[c].number * numbers2_kuohao[a][0];
                break;
            }
    }
    sum_of_atoms_numbers_kuohao *= *kuohao_out;
    sum_of_atoms_numbers = sum_of_atoms_numbers_kuohao + sum_of_atoms_numbers_in;
    printf("sum of numbers of chemical equation : %d\n", sum_of_atoms_numbers);
}

void kuohao_recognition(char examples[], char jituan[element_num][3],int numbers_of_kuohao_in[element_num][2], int numbers_of_kuohao_out[1])
{
    void recognition(char example[], char example2[element_num][3], int numbers1[element_num][1]);
    char  kuohao[length] = { 0 }, complete_array_kuohao_in[element_num][3] = { 0 }, complete_array_kuohao_out[4] = { 0 };
    int a, b, c, number_of_atoms_kuohao[element_num][1] = { 0 }, weizhi = 0, weishu = 0;
    for (a = 0; a < length; a++)
    {
        if (examples[a] == 40)
            weizhi = a;
        else if (examples[a] == 41)
        {
            for (b = 1; b <= 3; b++)//识别括号外的数字
                if (examples[a + b] >= 48 && examples[a + b] <= 57)
                {
                    complete_array_kuohao_out[b - 1] = examples[a + b] - 48;
                    weishu++;
                }
            break;
        }
    }
    for (c = 0, b = weizhi + 1; b < a; b++, c++)
        kuohao[c] = examples[b];
    recognition(kuohao,complete_array_kuohao_in,number_of_atoms_kuohao);//调用recognition处理好括号内的式子
    for (a = 0; a < element_num; a++)//输出处理好的基团所包含的元素信息（2维字符数组）
        for (b = 0; b < 3; b++)
            jituan[a][b] = complete_array_kuohao_in[a][b];
    for (a = 0; a < element_num; a++)
        for (b = 0; b < 2; b++)
            numbers_of_kuohao_in[a][b] = number_of_atoms_kuohao[a][b];
    numbers_of_kuohao_out[0] = pow(10, weishu - 1) * complete_array_kuohao_out[0] + pow(10, weishu - 2) * complete_array_kuohao_out[1] + pow(10, weishu - 3) * complete_array_kuohao_out[2];
}