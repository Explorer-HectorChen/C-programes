#include<iostream>
#include<string>
#include<limits>
using namespace std;
#define MAX 5//通讯录最大容量

//第一步，制作菜单
void menu()
{
    cout << "1.新建联系人" << endl;
    cout << "2.显示联系人" << endl;
    cout << "3.删除联系人" << endl;
    cout << "4.查找联系人" << endl;
    cout << "5.修改联系人" << endl;
    cout << "6.清空联系人" << endl;
    cout << "0.退出通讯录" << endl;
}

//第二步，两个结构体

//联系人结构体
struct person
{
    string NAME;//注意变量名不要混乱
    int SEX;
    string PHONENUMBER;
};//最后有分号

//通讯录结构体
struct Addressbook 
{
    struct person personArray[MAX];
    int size;
};


//第三步，添加联系人函数
void addPerson(Addressbook *ab)//用指针传实参，Addressbook是类型，ab是类型名
{
    if(ab->size == MAX)//容量不足的提醒
    {
        cout << "通讯录已满" << endl;
        return;
    }
    else
    {
        string name;//添加姓名
        cout << "请输入姓名：" << endl;
        getline(cin, name);
        ab -> personArray[ab->size].NAME = name;//学会这种写法

        cout << "性别：" << endl;//添加性别
        cout << "男——请输入1" << endl;
        cout << "女——请输入0" << endl;
        int sex = 0;
        //判断是否合理，并在输入不合理时用循环重置
        while(true)
        {
            cin >> sex;
            if(sex == 1||sex == 0)//输入正确
            {
                ab -> personArray[ab->size].SEX = sex;
                break;//跳出循环进入下一步-》输入号码
            }
            else//输入错误
            {
                cout << "请输入正确数字："<<endl;
                system("read -p '按回车键继续...' var");
            }//按回车重新开始循环
        }

        string phoneNumber;
        cout << "请输入号码：" <<endl;
        cin >> phoneNumber;
        ab -> personArray[ab->size].PHONENUMBER = phoneNumber;
        
        ab->size++;//总数+1
        cout << "添加成功" <<endl;
       
        
    }
}

//第四步，显示联系人函数
void show(Addressbook *ab)
{
    //先考虑特殊情况
    if(ab->size == 0)
    {
        cout << "当前通讯录为空" <<endl;
    }
    else//遍历数组并打印
    {
        for(int i = 0;i < ab->size;i++)
        {
            cout << "姓名："  << ab->personArray[i].NAME  << "\t" <<"性别：" << (ab->personArray[i].SEX ==1?"男":"女")<< "\t" << "号码：" << ab->personArray[i].PHONENUMBER<<endl;
            //判断男女，而不是输出数字
            

        }
    }
    //显示完以后提示用户离开
    system("read -p '按回车键继续...' var");
      
}

//第五步，删除联系人
void deletePerson(Addressbook *ab)
{
    cout << "请输入要删除的联系人姓名：" << endl;
    string name;
    getline(cin, name);
    for(int i = 0;i < ab->size;i++)
    {
        //检测联系人是否存在
        if(ab->personArray[i].NAME == name)
        {
            cout << "联系人" <<endl;
            cout << "姓名："  << ab->personArray[i].NAME  << "\t" <<"性别：" << (ab->personArray[i].SEX ==1?"男":"女")<< "\t" << "号码：" << ab->personArray[i].PHONENUMBER<<endl;
            for(int j = i;j < ab->size - 1;j++)
            {
                //数据迁移
                ab->personArray[j] = ab->personArray[j + 1];
            }
            ab->size--;
            
            cout << "已删除" << endl;
            return;
        }
    }
    cout << "未找到该联系人" << endl;
}

//第六步，查找联系人
void findPerson(Addressbook *ab)
{
    cout << "请输入要查找的联系人：" <<endl;
    string name;
    getline(cin,name);
    //首先判断通讯录是否为空
    if(ab->size == 0)
    {
        cout << "当前通讯录为空" <<endl;
    }
    else
    {
        for(int i = 0;i < ab->size;i++)
        {
            if(ab->personArray[i].NAME == name)
            {
                cout << "姓名："  << ab->personArray[i].NAME  << "\t" <<"性别：" << (ab->personArray[i].SEX ==1?"男":"女")<< "\t" << "号码：" << ab->personArray[i].PHONENUMBER<<endl;
                return;
            }
        }
        cout << "未找到该联系人" <<endl;
    }
}

//第七步，修改联系人
void modifyPerson(Addressbook *ab)
{
    cout << "请输入要修改的联系人姓名：" <<endl;
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');//清除输入缓冲区
    getline(cin,name);
    for(int i = 0;i < ab->size;i++)
    {
        if(ab->personArray[i].NAME == name)
        {
            cout << "请输入新的姓名：" <<endl;
            string newName;
            getline(cin,newName);
            ab->personArray[i].NAME = newName;
            cout << "请输入新的性别：" <<endl;
            cout << "男——请输入1" << endl;
            cout << "女——请输入0" << endl;
            int newSex;
            while(true)
            {
                cin >> newSex;
                if(newSex == 1||newSex == 0)
                {
                    ab->personArray[i].SEX = newSex;
                    break;
                }
                else
                {
                    cout << "请输入正确的数字：" <<endl;
                    system("read -p '按回车键继续...' var");
                }
            }
            cout << "请输入新的号码："  <<endl;
            string newPhoneNumber;
            cin >> newPhoneNumber;
            ab->personArray[i].PHONENUMBER = newPhoneNumber;
            cout << "修改成功" <<endl;
            return;
        }
    }
    cout << "未找到该联系人" <<endl;
}

//第八步，清空联系人
void clearPerson(Addressbook *ab)
{
    ab->size = 0;
    cout << "已清空联系人" <<endl;
}

int main()
{
    Addressbook ab;//声明一个Address类型的变量
    ab.size = 0;//初始化联系人数量
    //通过循环让用户能在执行一次操作以后重新开始，除了按0以外while一直循环
    while(true)
    {
        int select = 0;//选项
        system("clear");//每次使用前清屏
        menu();//展示菜单
        
        //避免错误输入
        if(!(cin >> select))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//清除输入缓冲区
            cout << "输入错误，请输入0~6之间的数字" << endl;
            system("read -p '按回车键继续...' var");
            system("clear");
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(select)
        {
        case 1:
        addPerson(&ab);//注意传地址才能修改值
            break;
        case 2:
        show(&ab);
            break;
        case 3:
            deletePerson(&ab);
            break;
        case 4:
            findPerson(&ab);
            break;
        case 5:
            modifyPerson(&ab);
            break;
        case 6:
            clearPerson(&ab);
            break;
        case 0:
            cout << "欢迎下次使用" << endl;
            system("read -p '按回车键继续...' var");
            return 0;
        default:
            cout << "输入错误，请输入0~6之间的数字" <<endl;
            break;    
        }
      system("read -p '按回车键继续...' var");
      
    }
}
