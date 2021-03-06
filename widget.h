#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QIcon>
#include <QStackedWidget>
#include <QPushButton>
#include <QSplitter>
#include <QMouseEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QToolButton>
#include <QSize>
#include <QFont>
#include <QPoint>
#include <QMediaPlayer>
#include <QSlider>
#include <QFrame>
#include <QStyle>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include "secframe.h"
#include "toolgroup/singlemusic.h"
#include "toolgroup/audiolist.h"
#include "lyric/lyricwidget.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~Widget();



protected:
    //还未实现，重现实现鼠标移动事件，使得窗体能够移动
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);



signals:
    //这个信号关联了整个程序的退出函数，而这个信号是由下面的quitEmit()函数发送的
    void quit();            //这里有个疑问：信号可以不用具体实现吗？？？

    void searchMusicString(QString);

//    //将信号发送歌词显示窗口，通知其歌曲播放了的时间值
//    void playedTimeLyric(qint64);



private slots:
    //关闭按钮的点击事件关联了这个槽函数，而这个槽函数会发送这个窗体的quit()信号
    void quitEmit();
    //点击最小化按钮所关联的槽函数
    void minWidget();

    //接收从secFrame传递过来的信号,在暂停与播放的控制之前，增添一个停止之前播放的
    //音乐功能，从而使得能够专注播放当前传递过来的歌曲，而停止其他任何歌曲
    void PreplayOrpauseMusic(SingleMusic *);
    //最顶层窗体，接收内层窗体发送过来的可以播放歌曲的信号,控制传递过来的歌曲的播放与暂停
    void playOrpauseMusic(SingleMusic *);

    //由按钮传递过来的信号，控制歌曲的播放
    void player();

    void setSliderValue(qint64);

    //搜索歌曲，将搜索框中文本传递给下载窗体的相关元素
    void searchMusic();

    //接收最底层的singlemusic.h窗体的通知，知道现在是在播放音乐
    void currentIsPlaying(bool);

    //接收从下层窗体过来的closePrevMusic信号，关闭之前播放的音乐
    void closePreMusic();

    //播放上一首歌曲，但暂时做测试用，之后换回真正的功能
    void prevMusic();

    //换肤
    void changeSkin();

//    //关联上歌词的滚动显示
//    void lyricScroll(qint64);



private:
    /***************************************************************/
    //整个窗体的主布局,是在垂直方向上再放三个子布局,因为要设置三个子布局有不同的大小，
    //所以主布局选择了QGridLayout
    QGridLayout *mainLayout;
    //第一个子布局
    QHBoxLayout *firstLayout;
    //第二个子布局
    QHBoxLayout *secondLayout;
    //第三个子布局
    QHBoxLayout *threeLayout;

    /****************************************************************/
    //第一个子布局上的元素
    //用户头像按钮及名字
    QPushButton *userImage;
    QPushButton *userName;
    QPixmap *userImagePix;

    //搜索框及其按钮
    QLineEdit *searchEdit;
    QPushButton *searchBtn;

    //皮肤按钮
    QPushButton *skinBtn;
    //设置按钮
    QPushButton *preferenceBtn;
    //控制器按钮
    QPushButton *controlBtn;
    //隐藏音乐库按钮
    QPushButton *hideBtn;
    //最小化按钮
    QPushButton *minimumBtn;
    //关闭按钮
    QPushButton *closeBtn;

    /*****************************************************************/
    //第二个子布局
    SecFrame *secFrameLayout;

    /******************************************************************/
    //第三个子布局上的元素
    //播放按钮
    QPushButton *playerBtn;
    bool playBool;              //用于控制播放按钮的形状
    //上一曲按钮
    QPushButton *preMusicBtn;
    //下一曲按钮
    QPushButton *nextMusicBtn;
    //我喜欢按钮
    QPushButton *loveMusicBtn;
    //下载按钮
    QPushButton *downloadBtn;
    //相似歌曲按钮
    QPushButton *similarBtn;
    //播放顺序按钮
    QPushButton *orderBtn;
    //音量按钮
    QPushButton *volumeBtn;
    //音效按钮
    QPushButton *soundEffectsBtn;
    //打开桌面歌词按钮
    QPushButton *lyricBtn;
    //播放队列按钮
    QPushButton *playQueueBtn;

    /***************进度条部件********************/
    //播放进度条
    QSlider *playSlider;
    //进度条上的音乐名
    QLabel *musicNameSlider;
    //进度条上的已播时间
    QLabel *playedTimeSlider;
    //进度条上的总时长
    QLabel *totalTimeSlider;
    //进度条的布局
    QHBoxLayout *upSliderLayout;
    QVBoxLayout *sliderLayout;
    //进度条的整体框架
    QFrame *sliderFrame;


    //另外，播放时间那个长条，先用addStretch()替上，之后要补上
    /***********************************************************************/

    //这是桌面背景 皮肤图片
    QPalette mainPalette;
    QPixmap skinPic = QPixmap(":/images/defaultBig.jpg");
    //字体
    QFont font;

    //保存鼠标按下位置的私有变量
    QPoint startPos;
    QPoint mousePos;
    QPoint disPos;

private:
    //设置背景图片
    void setSkin(QPixmap);

    //创建歌曲播放进度条，并关联歌曲的播放进度，同时尝试设置进度条的样式
    void createSlider();

public:
    //用于统一只播放一首歌曲
    SingleMusic *mainMusic;
    //歌曲名
    QString mainMusicName;
    //歌曲总时长
    qint64 mainMusicTotalTime;
    //歌曲已播放时长
    qint64 mainMusicPlayedTime;

    //用于统一只有一个列表被展开
    //AudioList *mainAudioList;

    //要搜索的歌曲名
    QString searchMusicName;




};

#endif // WIDGET_H
