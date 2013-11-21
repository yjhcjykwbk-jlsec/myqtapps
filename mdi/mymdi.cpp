#include "mymdi.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QPushButton>
#include <QCloseEvent>
#include <QMenu>

MyMdi::MyMdi(QWidget *parent) :
    QTextEdit(parent)//��ΪMyMdi�Ǽ̳�QTextEdit��ģ��������������һ���ı��༭�࣬���Ա༭����
{
    setAttribute(Qt::WA_DeleteOnClose);//���������������ô��ڵ���close()���������������ش��ڶ��ѣ�ͬʱҲ������
    is_saved_ = false;
}

void MyMdi::NewFile()
{
    static int sequence_number = 1;
    is_saved_ = false;
    current_file_path_ = tr("δ�����ĵ�%1.txt").arg(sequence_number++);
    setWindowTitle(current_file_path_ + "[*]");//�����ĵ�Ĭ�ϱ���,��[*]����Ĭ���������ʲô������ʾ�ģ�ֻ�е�����setWindowModified()
                                                //������ʱ�򣬻��Զ����ɡ�[*]���ĵط����ϡ�*������������ֻ��Զ�����
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(DocumentWasModified()));//�ĵ����ݷ����ı�ʱ��
                                                                                     //�����ۺ���DocumentWasModified().
}

QString MyMdi::CurrentFilePath()
{
    return current_file_path_;//current_file_path_��˽�б������������������ˣ�����CurrentFilePath()�ǹ��г�Ա��������ʾ����
}

//���õ�ǰ�ļ���һЩ��Ϣ������˵���ڱ��⣬���ļ���·������
void MyMdi::SetCurrentFile(const QString &file_name)
{
    current_file_path_ = QFileInfo(file_name).canonicalFilePath();//�õ����͹���ľ���·����
    is_saved_ = true;//����Ϊ�����������Ϊ�ú����Ǳ�LoadFile()�������õģ����Կ϶����Ա������Ǳ��������
    document()->setModified(false);//�ĵ�û�б��Ĺ�
    setWindowModified(false);//���ڲ���ʾ�����ĵı�־
    setWindowTitle(get_current_file_name() + "[*]");//���ô��ڱ���
}

bool MyMdi::LoadFile(const QString &file_name)
{
    QFile file(file_name);//������򿪵��ļ�����
    if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            //��ʧ��ʱ�����������Ϣ
            QMessageBox::warning(this, "���ĵ��༭��", tr("�޷���ȡ�ļ� %1��\n%2").arg(file_name).arg(file.errorString()));
            return false;
        }
    QTextStream in(&file);//�ı���
    QApplication::setOverrideCursor(Qt::WaitCursor);//��������Ӧ�ó���Ĺ����״Ϊ�ȴ���״����Ϊ����ļ������ݷǳ���ʱ���������û�
    setPlainText(in.readAll());//��ȡ�ı����е��������ݣ�����ʾ���䴰����
    QApplication::restoreOverrideCursor();//�ָ���ʼʱ�Ĺ��״̬
    SetCurrentFile(file_name);//���ñ���ʲô��
    //ע�����﷢���ź��õ���contentsChanged(),������contentsChange().
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(DocumentWasModified()));

    return true;
}

QString MyMdi::get_current_file_name()
{
    return QFileInfo(current_file_path_).fileName();//�ӵ�ǰ�ļ�·��������ȡ���ļ���
}

void MyMdi::DocumentWasModified()
{
    setWindowModified(document()->isModified());//��*����ʾ����

}

bool MyMdi::has_saved()
{
    if(document()->isModified())
        {
            QMessageBox box;
            box.setWindowTitle(tr("���ĵ��༭��"));
            box.setText(tr("�Ƿ񱣴��%1�ĸ��ģ�").arg(get_current_file_name()));
            box.setIcon(QMessageBox::Warning);//����ͼ��
            //��������Ϣbox�����3����ť���ֱ�Ϊyes��no��cancel
            QPushButton *yes_button = box.addButton(tr("��"), QMessageBox::YesRole);
            QPushButton *no_button = box.addButton(tr("��"), QMessageBox::NoRole);
            QPushButton *cancel_button = box.addButton(tr("ȡ��"), QMessageBox::RejectRole);
            box.exec();//������ȴ��û�ѡ��3����ť�е�һ��
            if(box.clickedButton() == yes_button)
                return Save();
            else if(box.clickedButton() == no_button)
                return true;//���ñ��棬ֱ�ӹص�
            else if(box.clickedButton() == cancel_button)
                return false;//ʲô������

        }
    return true;//Ҫô�Ѿ�������ˣ�Ҫô������û���Ĺ�������
}

bool MyMdi::Save()
{
    if(is_saved_)//�Ѿ����������һ�κ���˵���ļ����ļ������Ѿ�Ū���ˣ�ֱ�ӱ������ݼ��ɡ�
        return SaveFile(current_file_path_);
    else return SaveAs();//��һ�α���ʱ����Ҫ����SaveAs
}

bool MyMdi::SaveAs()
{
    //���ص�����file_name���Լ��ֶ���������֣�����ֱ�Ӳ��õ���Ĭ�ϵ�����
    QString file_name = QFileDialog::getSaveFileName(this, tr("���Ϊ"), current_file_path_);
    if(file_name.isEmpty())
        return false;

    return SaveFile(file_name);
}

bool MyMdi::SaveFile(const QString &file_name)
{
    QFile file(file_name);
    //��ʹ��д���ı���Ҳ�ý��ı��ȴ�
    if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this, "���ĵ��༭��", tr("�޷�д���ļ� %1��\n%2").arg(file_name).arg(file.errorString()));
            return false;
        }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();//�Դ��ı���ʽд�룬���ĺ���
    QApplication::restoreOverrideCursor();
    //����֮ǰ��Ҳ�����ļ��ı��⣬·���������úá�
    SetCurrentFile(file_name);
    return true;
}

void MyMdi::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu;

    //QKeySequence����ר�ŷ�װ��ݼ��ģ�����ʹ�õ���Ĭ�ϵĿ�ݼ����������ݼ�λ"&"�ź����Ǹ���ĸ
    QAction *undo = menu->addAction(tr("����(&U)"), this, SLOT(undo()), QKeySequence::Undo);//ֱ�ӵ��òۺ���undo()
    undo->setEnabled(document()->isUndoAvailable());//��Ϊ������һ��widget�����Կ���ֱ��ʹ��document()����

    QAction *redo = menu->addAction(tr("�ָ�(&A)"), this, SLOT(redo()), QKeySequence::Redo);
    redo->setEnabled(document()->isRedoAvailable());

    menu->addSeparator();//���ӷָ���

    QAction *cut = menu->addAction(tr("����(&T)"), this, SLOT(cut()), QKeySequence::Cut);
    cut->setEnabled(textCursor().hasSelection());

    QAction *copy = menu->addAction(tr("����(&C)"), this, SLOT(copy()), QKeySequence::Copy);
    copy->setEnabled(textCursor().hasSelection());

    menu -> addAction(tr("ճ��&P"), this, SLOT(paste()), QKeySequence::Paste);

    QAction *clear = menu->addAction(tr("���"), this, SLOT(clear()));
    clear->setEnabled(!document()->isEmpty());//�ı����ݷǿ�ʱ�Ϳ������

    menu->addSeparator();//���ӷָ���

    QAction *select_all = menu->addAction(tr("ȫѡ"), this, SLOT(selectAll()), QKeySequence::SelectAll);
    select_all->setEnabled(!document()->isEmpty());

    menu->exec(event->globalPos());//��ȡ���λ�ã�����ʾ�˵�

    delete menu;//��������˵�
}

//�ú����Ƕ��㴰�ڱ��ر�ʱ�������¼����ǹرմ����Դ��Ĺرշ���X
void MyMdi::closeEvent(QCloseEvent *event)//Ҫ�ǵü��� #include <QCloseEvent>
{
    if(has_saved())
        event->accept();//������Ϻ�ֱ���˳�����
    else
        event->ignore();

}
