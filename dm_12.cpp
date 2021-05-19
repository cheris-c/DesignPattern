#include <iostream>
using namespace std;

// Handle类，处理请求的接口：
class Handle {
protected:
    Handle* successor;
public:
    void SetSuccessor(Handle* s) {
        successor = s;
    }
    virtual void HandleRequest(int request) {
        successor->HandleRequest(request);
    }
};

// ConcreteHandler1 & ConcreteHandler2，具体处理类，处理其负责的请求，如果不能处理就将请求转发给它的后继者：
class ConcreteHandler1 : public Handle {
public:
    void HandleRequest(int request) {
        if (request == 1) cout << "HandleRequest1:" << request << endl;
        else if (successor != NULL) successor->HandleRequest(request);
    }
};

class ConcreteHandler2 : public Handle {
public:
    void HandleRequest(int request) {
        if (request == 2) cout << "HandleRequest2:" << request << endl;
        else if (successor != NULL) successor->HandleRequest(request);
    }
};

// 客户端代码实现：
int main() {
    int request1 = 1;
    int request2 = 2;

    Handle* h1 = new ConcreteHandler1();
    Handle* h2 = new ConcreteHandler2();

    h1->SetSuccessor(h2);   // 设置链
    h2->SetSuccessor(h1);

    h1->HandleRequest(request2);  // HandleRequest2:2
    h2->HandleRequest(request1);  // HandleRequest1:1
    delete h1;
    delete h2;
    return 0;
}