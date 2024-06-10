[1mdiff --git a/context.cpp b/context.cpp[m
[1mindex ee7e2ce..12b14f1 100644[m
[1m--- a/context.cpp[m
[1m+++ b/context.cpp[m
[36m@@ -16,7 +16,7 @@[m [mconst QMap<QString, qint64> & context::get_Map()[m
     return map;[m
 }[m
 [m
[31m-void context::f(const QString& size)[m
[32m+[m[32mvoid context::fill_Map(const QString& size)[m
 {[m
     this->strategy_->calculationMethod(size, map);[m
 }[m
[1mdiff --git a/context.h b/context.h[m
[1mindex 11c0540..1b4bb7d 100644[m
[1m--- a/context.h[m
[1m+++ b/context.h[m
[36m@@ -15,7 +15,7 @@[m [mpublic:[m
     ~context() = default;[m
 [m
     void set_Strategy(const std::shared_ptr<CalculationStrategy>& strategy);[m
[31m-    void f(const QString& size); // заполнить файл-размер[m
[32m+[m[32m    void fill_Map(const QString& size); // заполнить файл-размер[m
     const QMap<QString, qint64>& get_Map();[m
 };[m
 [m
[1mdiff --git a/main.cpp b/main.cpp[m
[1mindex 18c9618..a3038fc 100644[m
[1m--- a/main.cpp[m
[1m+++ b/main.cpp[m
[36m@@ -29,10 +29,14 @@[m [mint main(int argc, char *argv[])[m
 [m
 [m
     context context(std::make_shared<Folder_CalculationStrategy>());[m
[31m-    context.f(info);[m
[32m+[m[32m    context.fill_Map(info);[m
     print_Map(context.get_Map());[m
 [m
[32m+[m[32m    qDebug() << Qt::endl;[m
 [m
[32m+[m[32m    context.set_Strategy(std::make_shared<Type_CalculationStrategy>());[m
[32m+[m[32m    context.fill_Map(info);[m
[32m+[m[32m    print_Map(context.get_Map());[m
 [m
 [m
 [m
[1mdiff --git "a/tests/test1_repository/\320\221\320\270\320\273\320\265\321\202 6. \320\227\320\260\320\264\320\260\320\275\320\270\320\265 2.pdf" "b/tests/test1_repository/\320\221\320\270\320\273\320\265\321\202 6. \320\227\320\260\320\264\320\260\320\275\320\270\320\265 2.pdf"[m
[1mdeleted file mode 100644[m
[1mindex 872df66..0000000[m
[1m--- "a/tests/test1_repository/\320\221\320\270\320\273\320\265\321\202 6. \320\227\320\260\320\264\320\260\320\275\320\270\320\265 2.pdf"[m	
[1m+++ /dev/null[m
[36m@@ -1 +0,0 @@[m
[31m-[m
