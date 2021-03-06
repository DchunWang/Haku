#include "singledisplay.h"

SingleDisplay::SingleDisplay(QWidget *parent) : QWidget(parent)
{
    createDsingleInterface();

    //设置窗体的属性为关闭时也即可删除
    setAttribute(Qt::WA_DeleteOnClose);

    //设置窗体的背景颜色
    p.setColor(QPalette::Background, QColor(255, 255, 255, 0));
    setAutoFillBackground(true);
    setPalette(p);
}


void SingleDisplay::createDsingleInterface()
{
    singleCheckBox = new QCheckBox;
    DsingleMusicBtn = new QPushButton;
    DsingleMusicBtn->setFlat(true);
    //当鼠标单击歌曲名按钮时，就播放这首歌曲
    connect(DsingleMusicBtn, SIGNAL(clicked()), this, SLOT(playThisMusic()));

    DsingleAlbumBtn = new QPushButton;
    DsingleAlbumBtn->setFlat(true);
    DsingleTimeBtn = new QPushButton;
    DsingleTimeBtn->setFlat(true);

    DsinglePlayBtn = new QPushButton;
    DsinglePlayBtn->setFlat(true);
    DsinglePlayBtn->setIcon(QPixmap(":/images/tri_30.png"));
    //当鼠标单击播放按钮时，就播放这首歌曲
    connect(DsinglePlayBtn, SIGNAL(clicked()),
            this, SLOT(playThisMusic()));

    DsingleAddBtn = new QPushButton;
    DsingleAddBtn->setFlat(true);
    DsingleAddBtn->setIcon(QPixmap(":/images/addToList_30.png"));
    //当鼠标单击“添加”按钮时，就将这首歌曲自动添加到“试听音乐”列表
    connect(DsingleAddBtn, SIGNAL(clicked()),
            this, SLOT(addThisMusic()));

    DsingleDownloadBtn = new QPushButton;
    DsingleDownloadBtn->setFlat(true);
    DsingleDownloadBtn->setIcon(QPixmap(":/images/downloadIcon.png"));
    //当书包单击“下载”按钮时，就下载这首歌曲
    connect(DsingleDownloadBtn, SIGNAL(clicked()),
            this, SLOT(DsDownloadThisMusic()));

    threeBtnLayout = new QHBoxLayout;
    threeBtnLayout->setSpacing(0);
    threeBtnLayout->setMargin(0);
    threeBtnLayout->addWidget(DsinglePlayBtn);
    threeBtnLayout->addWidget(DsingleAddBtn);
    threeBtnLayout->addWidget(DsingleDownloadBtn);

    DsingleLayout = new QHBoxLayout(this);
    DsingleLayout->addWidget(singleCheckBox);
    DsingleLayout->addWidget(DsingleMusicBtn);
    DsingleLayout->addWidget(DsingleAlbumBtn);
    DsingleLayout->addWidget(DsingleTimeBtn);
    DsingleLayout->addStretch();
    DsingleLayout->addLayout(threeBtnLayout);
}

//当鼠标单击歌曲名按钮时，就播放这首歌曲
void SingleDisplay::playThisMusic()
{
    DsMusicName = DsingleMusicBtn->text();
    //发送信号，接收信号的上层窗体接收到要播放的歌曲名

    emit DsinglePlayThisMusic(DsMusicName);
}

//实现鼠标双击事件，仍是播放这首歌
void SingleDisplay::mouseDoubleClickEvent(QMouseEvent *)
{
//    playThisMusic();
}

//当鼠标单击 下载按钮时，就下载这首歌曲
void SingleDisplay::DsDownloadThisMusic()
{
    DsDownloadMusicName = DsingleMusicBtn->text();

    //发送信号 ，通知上层窗体要下载这首歌曲
    emit DsingleDownloadMusic(DsDownloadMusicName);
}

//当鼠标单击“添加”按钮时，将这首歌曲自动添加到“试听音乐”列表中
void SingleDisplay::addThisMusic()
{
    DsAddMusicName = DsingleMusicBtn->text();

    //发送信号，通知上层窗体要添加这首歌曲到“试听音乐"列表
    emit DsingleAddMusic(DsAddMusicName);
}

//重新实现进入窗体事件，使得当鼠标移进该首歌时能够显示不同的界面颜色
void SingleDisplay::enterEvent(QEvent *)
{
    p.setColor(QPalette::Background, QColor(255, 255, 255, 255));
    setPalette(p);
}
//重新实现离开窗体事件
void SingleDisplay::leaveEvent(QEvent *)
{
    p.setColor(QPalette::Background, QColor(255, 255, 255, 0));
    setPalette(p);
}
