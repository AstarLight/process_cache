# process_cache
C++11实现的进程LRU缓存，并提供数据持久化的方法

## 设计思路
1. 缓存使用LRU算法；
2. 持久化的序列化和反序列化；
3. 提供持久化策略：写db或者写本地文件；
4. 提供实时刷盘、周期批量刷盘策略。

## 代码结构
- object.cpp: 封装了写缓存和持久化的方法，读数据时先读LRU缓存，没命中则从持久化存储中取数据到内存，并回写缓存；
- lru_cache.cpp: LRU缓存
- persist_method.cpp: 数据持久化方法，写本地磁盘文件或者写DB；
- x2struct: 可以对C++内存对象序列化，然后用于数据落盘。 


## 编译 & 使用
编译
```
g++ -o test_cache  test_cache.cpp -std=c++11 -I x2struct/
```

使用
```
auto p = new object<int, User>(1000, "./game_users"); //参数为LRUcache 大小，存盘路径
User u1;  //定义要存储的对象
string key = "10086";
p->set_object(key, u1); //设置数据，参数：key 和 value
User x;
x = p->get_object(key);  // 取数据
```
