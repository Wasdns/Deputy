# Deputy: Department-to-Student bidirectional selection

[![Build Status](https://www.travis-ci.org/Wasdns/Deputy.svg?branch=master)](https://www.travis-ci.org/Wasdns/Deputy)

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

## Required Dependencies

- [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

## Usage

**For Ubuntu 14.04:**

1.First install jsoncpp:

```
$ sudo apt-get install libjsoncpp-dev
```

2.Compile the source codes:

```
$ cd Project/
$ ./compile.sh
```

3.Edit your input data in terms of JSON format and name your file as "input_data.json", such as [input_data.json](https://github.com/Wasdns/Deputy/blob/master/Project/test/input_data.json).

4.Execute the program:

```
$ ./main
```

The program will output the results to `output_data.json`.

5.Clean your environment:

```
$ ./cleanup.sh
```

**For Windows 10:**

```
> cd BIN/

// we assume that you have maintained 
// your input data in this directory
> test.exe
```

## Deputy-generator

We have implemented the generator of Deputy input data in this repo: 
[Deputy-generator](https://github.com/Wasdns/Deputy-generator).

For generating the input data, see the instructions 
[here](https://github.com/Wasdns/Deputy-generator/blob/master/README.md#usage).

## Test

For testing both the repositories, you could use the script named 
[check.sh](https://github.com/Wasdns/Deputy/blob/master/check.sh) to test the
correctness.

## Contact us

Mail: wasdnsxchen@gmail.com
