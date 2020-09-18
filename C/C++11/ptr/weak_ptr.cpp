
/*
https://www.cnblogs.com/DswCnblog/p/5628314.html

现在看，weak_ptr lock之后也是有可能内存泄漏的

*/

class A{
public:
    A(){ printf("[Line: %d] A constructor.. \n", __LINE__ ); }
    ~A(){ printf("[Line: %d] A destructor.. \n", __LINE__ ); }
};


int main()
{
    {
        shared_ptr<A> fsPtr(new A());
        weak_ptr<A> fwPtr = fsPtr;

        // weak_ptr不会改变shared_ptr，但是会和shared_ptr的引用保持一致
        cout << __LINE__ << " fsPtr use_count:" << fsPtr.use_count() << " fwPtr use_count:" << fwPtr.use_count() << endl;

        // fwPtr.lock()后会该变shared_ptr的引用计数(+1)
        // shared_ptr<A> fsPtr2 = fwPtr.lock();
        // cout << __LINE__ << " fsPtr use_count:" << fsPtr.use_count() << " fwPtr use_count:" << fwPtr.use_count() << endl;
        
        // 编译报错，weak_ptr没有重载*，->操作符，因此不可直接通过weak_ptr使用对象,只能通过lock()使用shared_ptr来操作
        // std::cout << " number is " << *fwPtr << std::endl;

        fsPtr.reset();
        cout << __LINE__ << " fsPtr use_count:" << fsPtr.use_count() << " fwPtr use_count:" << fwPtr.use_count() << endl;
        if (fwPtr.expired()) // true表示已被销毁，否则为false
        {
            cout << "shared_ptr object has been destory" << endl;
        }

        shared_ptr<A> fsPtr3 = fwPtr.lock();                //fsPtr3为NULL
        cout << " number is ";
        // cout<< *fsPtr3 << std::endl;　　　　 //运行时中断
    }
    return 0;
}

