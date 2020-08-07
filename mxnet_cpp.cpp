//
// Created by xijun1 on 2017/12/8.
//

#include <iostream>
#include <vector>
#include <string>
#include <mxnet/mxnet-cpp/MxNetCpp.h>
#include <mxnet/mxnet-cpp/op.h>

namespace mlp{

    template < typename T , typename U >
    class MLP{
    public:
        static mx_float OutputAccuracy(mx_float* pred, mx_float* target) {
            int right = 0;
            for (int i = 0; i < 128; ++i) {
                float mx_p = pred[i * 10 + 0];
                float p_y = 0;
                for (int j = 0; j < 10; ++j) {
                    if (pred[i * 10 + j] > mx_p) {
                        mx_p = pred[i * 10 + j];
                        p_y = j;
                    }
                }
                if (p_y == target[i]) right++;
            }
            return right / 128.0;
        }
        static bool train(T x , U y);
        static bool predict(T x);
        static bool net() {
            using mxnet::cpp::Symbol;
            using mxnet::cpp::NDArray;

            Symbol x = Symbol::Variable("X");
            Symbol y = Symbol::Variable("label");

            std::vector<std::int32_t> shapes({512 , 10});
            //定义一个两层的网络. wx + b
            Symbol weight_0 = Symbol::Variable("weight_0");
            Symbol biases_0 = Symbol::Variable("biases_0");

            Symbol fc_0 = mxnet::cpp::FullyConnected("fc_0",x,weight_0,biases_0 ,512);

            Symbol output_0 = mxnet::cpp::LeakyReLU("relu_0",fc_0,mxnet::cpp::LeakyReLUActType::kLeaky);

            Symbol weight_1 = Symbol::Variable("weight_1");
            Symbol biases_1 = Symbol::Variable("biases_1");
            Symbol fc_1 = mxnet::cpp::FullyConnected("fc_1",output_0,weight_1,biases_1,10);
            Symbol output_1 = mxnet::cpp::LeakyReLU("relu_1",fc_1,mxnet::cpp::LeakyReLUActType::kLeaky);
            Symbol pred = mxnet::cpp::SoftmaxOutput("softmax",output_1,y);  //目标函数，loss函数

            //定义使用计算驱动
            mxnet::cpp::Context ctx = mxnet::cpp::Context::cpu( 0);
            NDArray arr_x(mxnet::cpp::Shape( 128 , 28 ) , ctx , false);
            NDArray arr_y(mxnet::cpp::Shape(128) , ctx , false );

            //定义输入数据
            std::shared_ptr< mx_float > aptr_x(new mx_float[128*28] , [](mx_float* aptr_x){ delete [] aptr_x ;});
            std::shared_ptr< mx_float > aptr_y(new mx_float[128] , [](mx_float * aptr_y){ delete [] aptr_y ;});

            //初始化数据
            for(int i=0 ; i<128 ; i++){
                for(int j=0;j<28 ; j++){
                    //定义x
                    aptr_x.get()[i*28+j]= i % 10 +0.1f;
                }

                //定义y
                aptr_y.get()[i]= i % 10;
            }

            //将数据转换到NDArray中
            arr_x.SyncCopyFromCPU(aptr_x.get(),128*28);
            arr_x.WaitToRead();

            arr_y.SyncCopyFromCPU(aptr_y.get(),128);
            arr_y.WaitToRead();

            //定义各个层参数的数组
            NDArray arr_w_0(mxnet::cpp::Shape(512,28),ctx, false);
            NDArray arr_b_0(mxnet::cpp::Shape( 512 ),ctx,false);
            NDArray arr_w_1(mxnet::cpp::Shape(10 , 512 ) , ctx , false);
            NDArray arr_b_1(mxnet::cpp::Shape( 10 ) , ctx , false);

            //初始化权重参数
            arr_w_0 = 0.01f;
            arr_b_1 = 0.01f;
            arr_w_1 = 0.01f;
            arr_b_1 = 0.01f;

            //求解梯度

            NDArray arr_w_0_g(mxnet::cpp::Shape( 512 , 28 ),ctx, false);
            NDArray arr_b_0_g(mxnet::cpp::Shape( 512 ) , ctx , false);
            NDArray arr_w_1_g(mxnet::cpp::Shape( 10 , 512 ) , ctx , false);
            NDArray arr_b_1_g(mxnet::cpp::Shape( 10 ) , ctx , false);

            //将数据绑定到网络图中.

            //输入数据参数
            std::vector< NDArray > bind_data;
            bind_data.push_back( arr_x );
            bind_data.push_back( arr_w_0 );
            bind_data.push_back( arr_b_0 );
            bind_data.push_back( arr_w_1 );
            bind_data.push_back( arr_b_1 );
            bind_data.push_back( arr_y );

            //所有的梯度参数
            std::vector< NDArray > arg_grad_store;
            arg_grad_store.push_back( NDArray() ); //不需要输入的梯度
            arg_grad_store.push_back( arr_w_0_g );
            arg_grad_store.push_back( arr_b_0_g );
            arg_grad_store.push_back( arr_w_1_g );
            arg_grad_store.push_back( arr_b_1_g );
            arg_grad_store.push_back( NDArray() ); //不需要输出 loss 的梯度

            //如何操作梯度.
            std::vector< mxnet::cpp::OpReqType > grad_req_type;

            grad_req_type.push_back(mxnet::cpp::kNullOp);
            grad_req_type.push_back(mxnet::cpp::kWriteTo);
            grad_req_type.push_back(mxnet::cpp::kWriteTo);
            grad_req_type.push_back(mxnet::cpp::kWriteTo);
            grad_req_type.push_back(mxnet::cpp::kWriteTo);
            grad_req_type.push_back(mxnet::cpp::kNullOp);

            //定义一个状态数组
            std::vector< NDArray > aux_states;

            std::cout<<" make the Executor"<<std::endl;

            std::shared_ptr<mxnet::cpp::Executor > executor
                    = std::make_shared<mxnet::cpp::Executor>(
                            pred,
                            ctx,
                            bind_data,
                            arg_grad_store,
                            grad_req_type,
                            aux_states );
            //训练
            std::cout<<" Training "<<std::endl;

            int max_iters = 20000;  //最大迭代次数
            mx_float learning_rate = 0.0001; //学习率

            for (int iter = 0; iter < max_iters ; ++iter) {
                executor->Forward(true);
                if(iter % 100 == 0){
                    std::vector<NDArray> & out = executor->outputs;
                    std::shared_ptr<mx_float> tp_x( new mx_float[128*28] ,
                                                   [](mx_float * tp_x){ delete [] tp_x ;});
                    out[0].SyncCopyToCPU(tp_x.get(),128*10);
                    NDArray::WaitAll();
                    std::cout<<"epoch "<<iter<<"  "<<"Accuracy: "<<  OutputAccuracy(tp_x.get() , aptr_y.get())<<std::endl;
                }
                //依据梯度更新参数
                executor->Backward();
                for (int i = 1; i <5 ; ++i) {
                    bind_data[i] -= arg_grad_store[i]*learning_rate;
                }
                NDArray::WaitAll();
            }

        }
        static bool SetDriver();
    };

    template <typename T , typename U >
    bool MLP<T,U>::SetDriver() {
        return true;
    }
    template <typename T , typename U >
    bool MLP<T,U>::train(T x, U y) {
        return true;
    }
    template <typename T , typename U >
    bool MLP<T,U>::predict(T x) {
        return true;
    }

}


int main(int argc , char * argv[]){
    mlp::MLP<mx_float ,mx_uint>::net();
    MXNotifyShutdown();
    return 0;
}