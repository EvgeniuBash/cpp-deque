#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include "algo.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model()
{
    ui->setupUi(this);
    updateButtonState();
    connect(ui->list_widget, &QListWidget::currentRowChanged, this, &MainWindow::on_list_widget_currentRowChanged);
    std::random_device rd;
    rng_ = std::mt19937(rd());
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::updateButtonState() {

    ui->btn_pop_back->setDisabled(model.items.empty());
    ui->btn_erase->setDisabled(model.items.empty());
    ui->btn_pop_front->setDisabled(model.items.empty());
    ui->btn_dec_iterator->setDisabled(model.items.empty());
    ui->btn_inc_iterator->setDisabled(model.items.empty());
    ui->pb_edit->setDisabled(model.items.empty());
    ui->btn_dec_iterator->setDisabled(model.iterator == model.items.begin());
}

void MainWindow::ApplyModel() {
    model.iterator = model.items.begin();
    ui->list_widget->clear();
    for(size_t x = 0; x < model.items.size(); ++x ) {
        ui->list_widget->addItem(QString::fromStdString(std::to_string(x) + ": " + model.items[x]));
    }
    ui->txt_size->setText(QString::number(model.items.size()));
    ui->list_widget->addItem("end");
    ApplyIterator();
    updateButtonState();
}

void MainWindow::on_btn_tea_clicked()
{
    static std::deque<std::string> tea {
        "Чай Лунцзин",
        "Эрл Грей",
        "Сенча",
        "Пуэр",
        "Дарджилинг",
        "Ассам",
        "Матча",
        "Ганпаудер",
        "Оолонг",
        "Лапсанг Сушонг"
    };
    model.items = tea;
    ApplyModel();
}


void MainWindow::on_btn_cakes_clicked()
{
    static std::deque<std::string> cakes {
        "Красный бархат",
        "Наполеон",
        "Медовик",
        "Тирамису",
        "Прага",
        "Чизкейк",
        "Захер",
        "Эстерхази",
        "Морковный торт",
        "Чёрный лес",
    };
    model.items = cakes;
    ApplyModel();
}


void MainWindow::on_btn_pop_back_clicked()
{
    if (!model.items.empty()) {
        model.items.pop_back();
        ApplyModel();
    }
    updateButtonState();
}


void MainWindow::on_btn_push_back_clicked()
{
    QString text1 =  ui->txt_elem_content->text();
    model.items.push_back(text1.toStdString());
    ApplyModel();
    updateButtonState();
}


void MainWindow::on_btn_clear_clicked()
{
    model.items.clear();
    ui->btn_pop_back->setDisabled(true);
    ApplyModel();
}

void MainWindow::ApplyIterator() {
    auto index = std::distance(model.items.begin(), model.iterator);
    ui->list_widget->setCurrentRow(index);
    bool isEnd = (model.iterator == model.items.end());
    ui->pb_edit->setDisabled(isEnd);
    ui->btn_erase->setDisabled(isEnd);
    ui->btn_inc_iterator->setDisabled(isEnd);
    ui->txt_elem_content->setText(isEnd ? "" : QString::fromStdString(*model.iterator));

    bool isBegin = (model.iterator == model.items.begin());
    ui->btn_dec_iterator->setDisabled(isBegin);

}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow < 0) {
        return;
    }
    model.iterator = model.items.begin() + currentRow;
    ApplyIterator();
}
void MainWindow::on_btn_erase_clicked()
{
    int currentRow = ui->list_widget->currentRow();
    model.items.erase(model.items.begin() + currentRow);
    model.iterator = model.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_edit_clicked()
{
    int currentRow = ui->list_widget->currentRow();
    if (currentRow < 0) {
        return;
    }
    QString Q = ui->txt_elem_content->text();
    model.items[currentRow] = Q.toStdString();
    ApplyModel();
    ApplyIterator();

    ui->list_widget->setCurrentRow(currentRow);
}


void MainWindow::on_btn_insert_clicked()
{
    int currentRow = ui->list_widget->currentRow();
    QString Q = ui->txt_elem_content->text();
    model.items.insert(model.items.begin() + currentRow, Q.toStdString());
    model.iterator = model.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_dec_iterator_clicked()
{
    if (model.iterator != model.items.begin()) {
        --model.iterator;
        ApplyIterator();
    }
}


void MainWindow::on_btn_inc_iterator_clicked()
{
    if (model.iterator != model.items.end()) {
        ++model.iterator;
        ApplyIterator();
    }
}


void MainWindow::on_btn_begin_clicked()
{
    model.iterator = model.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_end_clicked()
{
    model.iterator = model.items.end();
    ApplyIterator();
}


void MainWindow::on_pb_resize_clicked()
{
    QString sizeText = ui->txt_size->text();
    int S = sizeText.toInt();
    model.items.resize(S);
    ApplyModel();
}


void MainWindow::on_pb_find_clicked()
{
    auto text = ui->txt_elem_content->text();
    auto find_text = std::find(model.items.begin(), model.items.end(), text.toStdString());
    model.iterator = model.items.end();
    ApplyIterator();
    if (find_text != model.items.end()) {
        model.iterator = find_text;
        ApplyIterator();
    } else {
        model.iterator = model.items.end();
        ApplyIterator();
    }
}


void MainWindow::on_pb_count_clicked()
{
    auto text = ui->le_count->text();
    auto count_text = std::count(model.items.begin(), model.items.end(), text.toStdString());
    ui->lbl_count->setText(QString::number(count_text));
    ApplyIterator();
}


void MainWindow::on_pb_min_clicked()
{
    if (model.items.empty()) {
        return;
    }
    auto Lh = std::min_element(model.items.begin(), model.items.end());
    model.iterator = Lh;
    ApplyIterator();
}



void MainWindow::on_pb_max_clicked()
{
    if (model.items.empty()) {
        return;
    }
    auto Wh = std::max_element(model.items.begin(), model.items.end());
    model.iterator = Wh;
    ApplyIterator();
}

void MainWindow::SetRandomGen(const std::mt19937& random_gen) {
    rng_ = random_gen;
}

void MainWindow::on_pb_sort_clicked()
{
    Comp comparator;
    model.items = MergeSort(model.items, comparator);
    model.iterator = model.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_SORT_clicked()
{
    auto caseComparator = [](const std::string& s1, const std::string& s2) {
        return QString::compare(QString::fromStdString(s1), QString::fromStdString(s2), Qt::CaseInsensitive) < 0;
    };
    model.items = MergeSort(model.items, caseComparator);
    model.iterator = model.items.begin();
    ApplyModel();
}


void MainWindow::on_pb_unique_clicked()
{
    if (std::is_sorted(model.items.begin(), model.items.end())) {
        auto to_del = std::unique(model.items.begin(), model.items.end());
        model.items.erase(to_del, model.items.end());
        ApplyModel();
    }
}


void MainWindow::on_pb_reverse_clicked()
{
    int currentRow = ui->list_widget->currentRow();
    std::reverse(model.items.begin(), model.items.end());
    ApplyModel();
    ui->list_widget->setCurrentRow(currentRow);
}


void MainWindow::on_pb_snuffle_clicked()
{
    int currentRow = ui->list_widget->currentRow();
    std::shuffle(model.items.begin(), model.items.end(), rng_);
    ApplyModel();
    ui->list_widget->setCurrentRow(currentRow);
}

void MainWindow::on_btn_push_front_clicked()
{
    QString text1 =  ui->txt_elem_content->text();
    model.items.push_front(text1.toStdString());
    ApplyModel();
    updateButtonState();
}


void MainWindow::on_btn_pop_front_clicked()
{
    if(model.items.empty()) {
        return;
    }
    model.items.pop_front();
    ApplyModel();
    updateButtonState();
}


void MainWindow::on_btn_lower_bound_clicked() {

    if (!std::is_sorted(model.items.begin(), model.items.end())) {
        return;
    }
    QString text1 = ui->txt_elem_content->text();
    std::string searchString = text1.toStdString();
    auto it = std::lower_bound(model.items.begin(), model.items.end(), searchString);
    model.iterator = it;
    ApplyIterator();
}

void MainWindow::on_btn_upper_bound_clicked()
{
    if (!std::is_sorted(model.items.begin(), model.items.end())) {
        return;
    }
    QString text1 = ui->txt_elem_content->text();
    std::string searchString = text1.toStdString();
    auto it = std::upper_bound(model.items.begin(), model.items.end(), searchString);
            model.iterator = it;
            ApplyIterator();
}
