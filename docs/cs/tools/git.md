#

* 什么是tag,以及版本号的规范
* git commit message 编写规范
* 几种修改提交记录的方法
* 远程仓库与github的本质
* 如何自行探索git存储的奥秘
* GitHub配置好邮箱的必要性
* issue和pull request

## 自学

version control with git
pro git

网站 learning git branching

## 什么是git

分布式（不联网）版本控制系统
linus 开发
远程与本地

### 配置

创建版本库
git init
 账号配置
 全局： git config--global .user.name"name"
        git config--global.user.email"email"
  针对某一版本库：
  去掉global

### 基础用法

#### 文件暂存

* 暂存区：已经修改，等待后续提交的文件
* 将文件加入暂存区：
  git add file/folder(只会修改添加过的文件)
  git add .（当前目录下所有修改过的文件）
* 删除文件的几种情况：
  * 只在本地删除版本库中不存在的文件：rm
  * 同时删除本地和版本库中的文件 git rm 
  * 将一个已暂存的新文件取消暂存：git rm --cached
* 重命名文件 git mv
* 查看当前工作区和暂存区状态：git status
三种文件状态：untracked ignore tracked
关于.gitigonre github模板

#### 提交更改

* 将暂存内容提交到本地仓库，生成一个新版本
  * git commit: 默认*编辑器*编辑提交信息
  * git commit -m "message"
  * -a(all)

* 查看提交历史：git log
  *---oneline:每一个提交一行
  *-graph:显示分支结构
  *-stat:显示文件删改信息
  *-p:显示详细的修改信息
* 每个提交都有唯一的sha-1的标识符（40位16进制）将提交的所有内容进行散列
  *gitshowid 显示提交详细信息（id在不重复的前提下可以只写前几位）
* 给出之前的某一版本：git checkout id(回到原来的状态)


#### 关于commit message

* 意义：记录更改的原因/内容、方便定位/回溯（特别是合作项目）
* angular规范

``` a
<type>([scope]):<summary>

[body]

[footer]

```

* type:更改类型（fix（修bug）/feat(添加新特性)/docs/refactor（重构）/perf（提高性能）/test/ci（持续集成）/……）
* scope：影响范围（可选）
* summary：简要描述
* body：更详细的描述

#### 版本 标签

* 创建标签
  *轻量标签：git tag id
  *附注标签：git tag -a tag -m"message" id
* 查看标签：git tag
* 版本号命名一般规范：semantic versioning 2.0.0
  * v主版本号.次版本号.修订号[-预发布版本号（可选）]
  * 修订号：兼容修改，修正不正确的行为
  * 次版本号：添加新功能但是保持兼容
  *主版号：不兼容的api修改
    * 0不稳定
  * 预发布版本号：alpha(内测)/beta（公测）/rc1./rc2.（release candidate）


#### detached head 问题

* 什么是head:当前工作区在提交历史中的指针
* 什么是detached（游离） head:head 指向某个历史提交，而不是某个”分支“
* 什么情况下会出现detached head
  * git checkout id,此后的修改不会出现在任何分支
  * 切换回master后会出现一条不属于任何分支的提交（相当于修改会丢失）



