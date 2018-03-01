#include "Compary.h"
#include "ConcreteCompany.h"
#include "FinanceDepartment.h"
#include "HRDepartment.h"

int main()
{
	Compary *root = new ConcreteCompany("�ܹ�˾");
	Compary *leaf1 = new HRDepartment("������Դ��");
	Compary *leaf2 = new FinanceDepartment("����");

	root->Add(leaf1);
	root->Add(leaf2);

	//�ֹ�˾A  
    Compary *mid1 = new ConcreteCompany("�ֹ�˾A");  
    Compary *leaf3=new FinanceDepartment("����");  
    Compary *leaf4=new HRDepartment("������Դ��");  
    mid1->Add(leaf3);  
    mid1->Add(leaf4);  
    root->Add(mid1);  
    //�ֹ�˾B  
    Compary *mid2=new ConcreteCompany("�ֹ�˾B");  
    FinanceDepartment *leaf5=new FinanceDepartment("����");  
    HRDepartment *leaf6=new HRDepartment("������Դ��");  
    mid2->Add(leaf5);  
    mid2->Add(leaf6);  
    root->Add(mid2);  
    root->Show(0);  
  
    delete leaf1; delete leaf2;  
    delete leaf3; delete leaf4;  
    delete leaf5; delete leaf6;   
    delete mid1; delete mid2;  
    delete root;  

	getchar();
    return 0;

}