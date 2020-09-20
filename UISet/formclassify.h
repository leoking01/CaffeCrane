#ifndef FORMCLASSIFY_H
#define FORMCLASSIFY_H

#include <QWidget>

namespace Ui {
class FormClassify;
}

class FormClassify : public QWidget
{
    Q_OBJECT
private:
    explicit FormClassify(QWidget *parent = nullptr);
    ~FormClassify();

public :
    static FormClassify *instance;
public:
    static FormClassify *getInstance() {
        if (instance) {
            return instance;
        } else {
            instance = new FormClassify();
        }
    }


private slots:
    void on_selClass01Dir_clicked();

    void on_selClass02Dir_clicked();

    void on_train_clicked();

    void on_selTestDir_clicked();

    void on_test_clicked();

private:
    Ui::FormClassify *ui;
};

#endif // FORMCLASSIFY_H
