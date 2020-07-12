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
    struct list_head mylist;
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

* 获取宿主结构地址的接口（理解即可，不直接调用）
```c
/*
ptr： 成员变量mem的地址    
type： 包含成员变量mem的宿主结构体的类型
member： 宿主结构中list_head成员变量名
*/
list_entry(ptr, type, member);

// 宏定义如下
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)
	
#define container_of(ptr, type, member) ({          \  
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \  
    (type *)( (char *)__mptr - offsetof(type,member) );})
    
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)  // 获取成员 MEMBER 在结构 TYPE 中的相对偏移量

// 结合上面自定义的结构
list_entry(&first_task.mylist, struct my_task_list, mylist);

/*
list_entry调用的container_of宏的功能就是根据 first_task.mylist字段的地址得出first_task结构的其实地址。
list_entry宏展开为
*/
const typeof( ((struct my_task_list *)0)->mylist ) *__mptr = (&first_task.mylist); \  
    (struct my_task_list *)( (char *)__mptr - ((size_t) &((struct my_task_list *)0)->mylist) );})   
/*
typeof 是 GNU对C新增的一个扩展关键字，用于获取一个对象的类型 ，比如这里((struct my_task_list *)0)->mylist 是把0地址强制转换成struct my_task_list 指针类型，然后取出mylist元素。 然后再对mylist元素做typeof操作，其实就是获取 my_task_list结构中mylist字段的数据类型struct list_head，所以这行语句最后转化为：
*/
const struct list_head *__mptr  = (&first_task.mylist);
/*
第二条语句中在用 __mptr这个指针 减去 mylist字段在 my_task_list中的偏移（把0地址强制转换成struct my_task_list指针类型，然后取出mylist的地址，此时mylist的地址也是相对于0地址的偏移，所以就是mylist字段相对于宿主结构类型struct my_task_list的偏移） 正好就是宿主结构的起始地址。
*/

```

* 遍历宿主结构（自定义结构）的接口
```c
list_for_each_entry(pos, head, member);

// 以上面的 my_task_list 结构为例
struct my_task_list *pos = NULL;  // 游标，不停移动 
list_for_each_entry (pos, &header_task, mylist) 
{ 
    printk("val =  %d\n" , pos_ptr->val); 
}

// 宏定义
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)
	
#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)
	
```
