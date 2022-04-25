#include<iostream>
#include<vector>
#include<cmath>

class Figure{
    public:
    std::pair<float, float> get_center(){
        return center;
    };
    void radrota(){
        std::cout<<"Radius is "<<radius<<'\n';
        std::cout<<"Side is "<<a<<'\n';
    }
    virtual float area(){return 0.0;}
    virtual void print_cords(){}

    protected:
    std::pair<float, float> center;
    float radius;
    int number;
    int a;
    Figure(){
        radius=0;
        center=std::make_pair(NAN,NAN);
        a=0;
    }
};

class Triangle : public Figure
{
    public:
    Triangle(){
        number=3;
    }
    Triangle(float centx, float centy, float rad){
        number=3;
        center.first=centx;
        center.second=centy;
        radius=rad;
    }
    virtual float area() override{
        return sqrt(3.0)*3.0/4.0;
    }
    virtual void print_cords() override{
        std::pair<float, float> cords;
        std::cout<<"Triangle cords:\n";
        for(int i=0; i<number; i++){
            cords=center;
            cords.first+=radius*cos((2.0*i/number)*M_PI);
            cords.second+=radius*sin((2.0*i/number)*M_PI);
            std::cout<<"  "<<cords.first<<", "<<cords.second<<'\n';
        }
    }
};

class Square : public Figure
{
    public:
    Square(){
        number=4;
    }
    Square(float centx, float centy, float rad){
        number=4;
        center.first=centx;
        center.second=centy;
        radius=rad;
    }
    virtual float area() override{
        return number*radius*radius/2.0;
    }
    virtual void print_cords() override{
        std::pair<float, float> cords;
        std::cout<<"Square cords:\n";
        for(int i=0; i<number; i++){
            cords=center;
            cords.first+=radius*cos((2.0*i/number + 1.0/4.0)*M_PI);
            cords.second+=radius*sin((2.0*i/number + 1.0/4.0)*M_PI);
            std::cout<<"  "<<cords.first<<", "<<cords.second<<'\n';
        }
    }
};

class Rectangle : public Figure
{
    public:
    Rectangle(){
        number=4;
    }
    Rectangle(float centx, float centy, float rad, float b){
        number=4;
        center.first=centx;
        center.second=centy;
        radius=rad;
        a=b;
    }
    virtual float area() override{
        return sqrt(radius*radius*4.0-a*a)*a;
    }
    virtual void print_cords() override{
        int b=sqrt(radius*radius*4.0-a*a);
        std::cout<<"Rectangle cords:\n";
        std::cout<<"  "<<center.first+a/2.0<<", "<<center.second+b/2.0<<'\n';
        std::cout<<"  "<<center.first+a/2.0<<", "<<center.second-b/2.0<<'\n';
        std::cout<<"  "<<center.first-a/2.0<<", "<<center.second+b/2.0<<'\n';
        std::cout<<"  "<<center.first-a/2.0<<", "<<center.second-b/2.0<<'\n';
    }
};

void print_areas_sum(std::vector<Figure*> array){
    float sum=0.0;
    for(int i=0; i<array.size(); i++){
        sum+=array[i]->area();
    }
    std::cout<<"Summary area is "<<sum<<'\n';
}

void do_methods(std::vector<Figure*> array){
    std::pair<float, float> tmp;
    for(int i=0; i< array.size(); i++){
        std::cout<<"Figure number "<<i<<":\n";
        std::cout<<"  area: "<<array[i]->area()<<'\n';
        std::cout<<"  center: ";
        tmp=array[i]->get_center();
        std::cout<<tmp.first<<", "<<tmp.second<<'\n';
        array[i]->print_cords();
        array[i]->radrota();
    }
}

int main(){
    std::cout<<"t - create triangle\n\
    s - create square\n\
    r - create rectangle\n\
    a - calculate summary area\n\
    m - print results of method's execution for every figure\n\
    d - delete figure\n\
    q - quit\n";
    char c;
    std::vector<Figure*> array;
    int i;
    float rad, centx, centy, a;
    while(1){
        std::cout<<"Enter comand:\n";
        std::cin>>c;
        switch(c){
            case 't':
                {std::cout<<"Enter center cords and radius:\n";
                std::cin>>centx>>centy>>rad;
                Figure *ref=new Triangle(centx, centy,rad);
                array.push_back(ref);
                break;}
            case 's':
                {std::cout<<"Enter center cords and radius:\n";
                std::cin>>centx>>centy>>rad;
                Figure *ref= new Square(centx, centy,rad);
                array.push_back(ref);
                break;}
            case 'r':
                {std::cout<<"Enter center cords, radius and wide side:\n";
                std::cin>>centx>>centy>>rad>>a;
                Figure *ref= new Rectangle (centx, centy,rad, a);
                array.push_back(ref);
                break;}
            case 'a':
                {print_areas_sum(array);
                break;}
            case 'm':
                {do_methods(array);
                break;}
            case 'd':
                {std::cout<<"Enter number:\n";
                std::cin>>i;
                array.erase(array.begin()+i);
                break;}
            case 'q':
                return 0;
        }
    }
}
