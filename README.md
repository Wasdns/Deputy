# Deputy: Department-to-Student bidirectional selection

## [Requirements](http://www.cnblogs.com/easteast/p/7604534.html)

编码实现一个部门与学生的智能匹配的程序。
提供输入包括：

- 20个部门
- 部门编号（唯一确定值），字符；
- 各部门需要学生数的要求的上限，单个，数值，在[10,15]内；
- 各部门的特点标签，多个（两个以上），字符；
- 各部门的常规活动时间段，多个（两个以上），字符。
- 300个学生
- 学生编号（唯一确定值），字符；
- 学生空闲时间段，多个（两个以上），字符；
- 兴趣标签，多个（两个以上），字符（学生的兴趣标签一定是所有部门特点标签其中的一个）
- 每个学生有不多于5个的部门意愿（助教测试时测试数据中部门意愿可能会出现空缺，非空缺的部分一定是部门编号中的一个，并按照优先级从高到底的顺序排序）。

实现一个智能自动分配算法，根据输入信息，输出部门和学生间的匹配信息（一个学生可以确认多个他所申请的部门，一个部门可以分配少于等于其要求的学生数的学生） 及 未被分配到学生的部门 和 未被部门选中的学生。

## Usage

1.First install jsoncpp:

For Mac OSX environment:

```
// install homebrew
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" < /dev/null 2> /dev/null

// install jsoncpp
$ brew install jsoncpp
```

For Ubuntu14.04 environment(recommend):

```
$ sudo apt-get install libjsoncpp-dev
```

2.Compile the source codes(passed in Ubuntu 14.04 environment):

```
$ cd Project/
$ ./compile.sh
```

TODO

## Performance Examination

TODO
