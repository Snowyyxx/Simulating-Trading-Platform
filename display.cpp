#include"database.h"

int main(){
    int open_orders =0,closed_orders =0,partial_completed=0;
    while(true){
        sleep(3);
        json file = DisplayOrders();
        for(const auto & order : file){
            if(order["status"]=="Placed"){
                open_orders++;
            }else if (order["status"]=="Fully Executed"){
                closed_orders++;
            }
            else{
                partial_completed++;
            }
        }
        std::cout<<"No. of Open Orders: "<<open_orders<<", No. of executed orders: "<<closed_orders<<" and partially completed orders: "<<partial_completed<<std::endl;
    }
}