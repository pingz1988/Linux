* 定义
```c
struct list_head {
	struct list_head *next, *prev;  // 双向链表
};
```

围绕这个结构开始构建自己的链表，然后插入、删除节点 ，遍历整个链表等等，其实内核已经提供好了现成的接口.  

* 初始化
```c
struct list_head header_task;
INIT_LIST_HEAD(&header_task);  // 或者 LIST_HEAD(&header_task);
// 初始化后header_task的prev、next都指向自身，等同于struct list_head header_task = {&header_task,  &header_task};
```

* 宿主结构（链表，基于list_head的自定义结构）
```c
struct  my_task_list {
    int val ;
    struct list_head *mylist;
}
```

* 创建节点
```c
struct my_task_list first_task = 
{ .val = 1,
  .mylist = LIST_HEAD_INIT(first_task.mylist)
};  // mylist 的prev 和 next指针分别指向mylist自己
```

* 添加节点
```c
list_add(&my_first_task.mylist, &header_task);  // 头插法
list_add_tail(&my_first_task.mylist, &header_task);  // 尾插法
```

* 删除节点
```c
list_del(struct list_head *entry);
```

* list_head的遍历(还有替换、移位等操作)
```c
list_for_each(pos, head);
list_for_each_prev(pos, head);
```

* 获取宿主结构地址的接口
```c
/*
ptr： 成员变量mem的地址    
type： 包含成员变量mem的宿主结构体的类型
member： 宿主结构中list_head成员变量名
*/
list_entry(ptr, type, member);
```

* 遍历宿主结构的接口
```c
list_for_each_entry(pos, head, member);
// 以上面的 my_task_list 结构为例
struct my_task_list *pos = NULL;  // 游标，不停移动 
list_for_each_entry (pos, &header_task, mylist) 
{ 
    printk("val =  %d\n" , pos_ptr->val); 
}
```
