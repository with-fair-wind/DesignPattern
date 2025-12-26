# SOLID 设计原则

SOLID 是一个首字母缩写，代表以下设计原则（及其缩写）：

- 单一责任原则（SRP）
- 开闭原则（OCP）
- 里氏替换原则（LSP）
- 接口隔离原则（ISP）
- 依赖注入原则（DIP）

## 里氏替换原则

里氏替换原则（以 Barbara Liskov 命名）指出，如果一个接口可以接受类型为 Parent 的对象，那么它应该同样地可以接受类型为 Child 的对象，而不会有任何破坏

## DIP 的原始定义如下所示

*A. High-level modules should not depend on low-level modules. Both should depend on abstractions*.(高层模块不应该依赖低层模块，两个都应该依赖抽象)
*B. Abstractions should not depend on details. Details should depend on abstractions.*(抽象不应该依赖细节，细节应该依赖抽象)

