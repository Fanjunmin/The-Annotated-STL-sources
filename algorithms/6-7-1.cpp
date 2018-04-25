//filename 6-7-1.cpp

#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T>
struct display {
    void operator() (const T& x) const {
        cout << x << ' ';
    }
};

struct even {
    bool operator() (int x) const {
        return x % 2 ? false : true;
    }
};

struct even_by_two {
public:
    int operator()() const {
        return _x += 2;
    }
private:
    static int _x;
};

int even_by_two::_x = 0;

int main()
{
    int ia[11] = {0,1,2,3,4,5,6,6,6,7,8};
    vector<int> iv(ia, ia+sizeof(ia)/sizeof(int));

    //找到第一组相邻元素相等
    cout << *adjacent_find(iv.begin(), iv.end()) << endl;   //6
    cout << *adjacent_find(iv.begin(), iv.end(), equal_to<int>()) << endl;   //6

    //找到值为6的元素个数
    cout << count(iv.begin(), iv.end(), 6) << endl; //3

    //找到所有小于7元素的个数
    cout << count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) << endl;    //9

    //找到元素值为4的第一个元素的位置的值
    cout << *find(iv.begin(), iv.end(), 4) << endl; //4

    //找到大于2的第一个元素的所在位置
    cout << find_if(iv.begin(), iv.end(), bind2nd(greater<int>(), 2)) - iv.begin() << endl; //3

    //找到子序列iv2所出现的最后一个出现的位置
    vector<int> iv2(ia + 6, ia + 8); //{6,6}
    cout << *(find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end())) << endl;  //6

    //找到子序列iv2所出现的第一个出现的位置
    cout << *(find_first_of(iv.begin(), iv.end(), iv2.begin(), iv2.end())) << endl; //6

    //遍历区间执行display()操作
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl;

    //遍历iv2区间，对每个元素实行even_by_two操作
    //generate()函数的第三个参数（仿函数）本身不得有参数
    generate(iv2.begin(), iv2.end(), even_by_two()); //改变了元素的内容
    //generate(iv2.begin(), iv2.end(), bind2nd(plus<int>(), 2));  //error
    for_each(iv2.begin(), iv2.end(), display<int>()); cout << endl;     //2 4

    //迭代指定区间，对每个元素执行even_by_two操作
    generate_n(iv.begin(), 3, even_by_two());
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl;     //6,8,10,3,4,5,6,6,6,7,8

    //删除元素6(实际是copy),尾端可能有残余数据
    remove(iv.begin(), iv.end(), 6);
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl;   //8 10 3 4 5 7 8 {6 6 7 8} 大括号里的为残余数据

    //删除元素6，结果置于另外区间
    vector<int> iv3(12);
    remove_copy(iv.begin(), iv.end(), iv3.begin(), 6);
    for_each(iv3.begin(), iv3.end(), display<int>()); cout << endl; //8 10 3 4 5 7 8 7 8 {0 0 0}

    //删除小于6元素
    remove_if(iv.begin(), iv.end(), bind2nd(less<int>(), 6));
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl;   //8 10 7 8 6 6 7 8 {6 7 8}

    //删除小于7元素，并置于另外区间
    remove_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(less<int>(), 7));
    for_each(iv3.begin(), iv3.end(), display<int>()); cout << endl; //8 10 7 8 7 8 7 8 {8 0 0 0}

    //将值为6的元素改为值为3
    replace(iv.begin(), iv.end(), 6, 3);
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl;   //8 10 7 8 3 3 7 8 3 7 8

    //将值为3的元素改为5并且置于另外区间
    replace_copy(iv.begin(), iv.end(), iv3.begin(), 3, 5);
    for_each(iv3.begin(), iv3.end(), display<int>()); cout << endl; //8 10 7 8 5 5 7 8 5 7 8 {0}

    //将值小于5的元素改为2
    replace_if(iv.begin(), iv.end(), bind2nd(less<int>(), 5), 2);
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl; //8 10 7 8 2 2 7 8 2 7 8

    //将所有值为8的元素改为9并置于其他区间
    replace_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(equal_to<int>(), 8), 9);
    for_each(iv3.begin(), iv3.end(), display<int>()); cout << endl; //9 10 7 9 2 2 7 9 2 7 9 {0}

    //逆向重排每一个元素
    reverse(iv.begin(), iv.end());
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl;   //8 7 2 8 7 2 2 8 7 10 8

    //逆向重排每一个元素并且置于另外区间
    reverse_copy(iv.begin(), iv.end(), iv3.begin());
    for_each(iv3.begin(), iv3.end(), display<int>()); cout << endl; //8 10 7 8 2 2 7 8 2 7 8 {0}

    //旋转互换元素
    rotate(iv.begin(), iv.begin() + 4, iv.end());
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl; //7 2 2 8 7 10 8 8 7 2 8

    //旋转互换元素并且置于另外区间
    rotate_copy(iv.begin(), iv.begin() + 4, iv.end(), iv3.begin());
    for_each(iv3.begin(), iv3.end(), display<int>()); cout << endl; //8 7 2 8 7 2 2 8 7 10 8 {0}

    //查找某一个子序列第一次出现的位置
    int ia2[3] = {2, 8};
    vector<int>  iv4(ia2, ia2 + 2); //iv4 = {2, 8}
    cout << (search(iv.begin(), iv.end(), iv4.begin(), iv4.end()) - iv.begin()) << endl;  //2

    //查找连续两个8第一次出现的位置
    cout << (search_n(iv.begin(), iv.end(), 2, 8) - iv.begin()) << endl;  //6

    //查找连续3个8第一次出现的位置
    cout << (search_n(iv.begin(), iv.end(), 3, 8) - iv.begin()) << endl;    //11 = iv.size()

    //查找连续3个值小于8第一次出现的位置
    cout << (search_n(iv.begin(), iv.end(), 3, 8, less<int>()) - iv.begin()) << endl;   //0

    //将两个区间互换，第二个区间的元素不应该小于第一个区间的元素的个数
    swap_ranges(iv4.begin(), iv4.end(), iv.begin());
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl;   //2 8 2 8 7 10 8 8 7 2 8
    for_each(iv4.begin(), iv4.end(), display<int>()); cout << endl; //7 2

    //改变区间的值，全部减2
    transform(iv.begin(), iv.end(), iv.begin(), bind2nd(minus<int>(), 2));
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl;   //0 6 0 6 5 8 6 6 5 0 6

    //改变区间的值，令第二区间的元素值加到第一区间的对应元素身上，第二个区间的元素不应该小于第一个区间的元素的个数
    transform(iv.begin(), iv.end(), iv.begin(), iv.begin(), plus<int>());
    for_each(iv.begin(), iv.end(), display<int>()); cout << endl; //0 12 0 12 10 16 12 12 10 0 12

    //****************************************

    vector<int> iv5(ia, ia + sizeof(ia) / sizeof(int)); //0,1,2,3,4,5,6,6,6,7,8
    vector<int> iv6(ia + 4, ia + 8);    //4 5 6 6
    vector<int> iv7(15);    //0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    for_each(iv5.begin(), iv5.end(), display<int>()); cout << endl; //0,1,2,3,4,5,6,6,6,7,8
    for_each(iv6.begin(), iv6.end(), display<int>()); cout << endl; //4 5 6 6

    cout << *(max_element(iv5.begin(), iv5.end())) << endl;  //8
    cout << *(min_element(iv6.begin(), iv6.end())) << endl;   //4

    //判断iv6所有元素是否在iv5中，两个序列必须都有序
    cout << includes(iv5.begin(), iv5.end(), iv6.begin(), iv6.end()) << endl;   //1(true)

    //将有序的序列iv5 iv6合并成另一个有序序列
    merge(iv5.begin(), iv5.end(), iv6.begin(), iv6.end(), iv7.begin());
    for_each(iv7.begin(), iv7.end(), display<int>()); cout << endl; //0 1 2 3 4 4 5 5 6 6 6 6 6 7 8

    //符合条件的放在容器前段，不符合放在后段，不保证相对次序（不稳定）
    partition(iv7.begin(), iv7.end(), even());
    for_each(iv7.begin(), iv7.end(), display<int>()); cout << endl; //0 8 2 6 4 4 6 6 6 6 5 5 3 7 1

    //去除连续重复元素
    unique(iv5.begin(), iv5.end());
    for_each(iv5.begin(), iv5.end(), display<int>()); cout << endl; //0 1 2 3 4 5 6 7 8 {7 8}

    //去除连续重复元素并且置于另外区间
    unique_copy(iv5.begin(), iv5.end(), iv7.begin());
    for_each(iv7.begin(), iv7.end(), display<int>()); cout << endl; //0 1 2 3 4 5 6 7 8 7 8 {5 3 7 1}

    return 0;
}
