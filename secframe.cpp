#include "secframe.h"

SecFrame::SecFrame(QWidget *parent)
    : QFrame(parent)
{
    //设置它的透明度
    setWindowOpacity(0.8);
    //设置鼠标捕捉
    //setMouseTracking(true);
    //主布局
    secMainLayout = new QHBoxLayout(this);

    /******************************************************************************/
    //第一个小布局上的按钮实现
    musicListBtn = new QPushButton;
    musicListBtn->setFlat(true);
    musicListBtn->setFixedSize(50, 50);
    musicListBtn->setIcon(QPixmap(":/images/musicListIcon.png"));
    musicListBtn->setIconSize(QPixmap(":/images/musicListIcon.png").size());
    musicListBtn->setToolTip(tr("音乐列表"));

    favoriteBtn = new QPushButton;
    favoriteBtn->setFlat(true);
    favoriteBtn->setFixedSize(50, 50);
    favoriteBtn->setIcon(QPixmap(":/images/favoriteIcon.png"));
    favoriteBtn->setIconSize(QPixmap(":/images/favoriteIcon.png").size());
    favoriteBtn->setToolTip(tr("我的收藏"));

//    fmBtn = new QPushButton;
//    fmBtn->setFlat(true);
//    //fmBtn->setFixedSize(50, 50);
//    fmBtn->setIcon(QPixmap(":/images/fmBtn.png"));
//    fmBtn->setIconSize(QPixmap(":/images/fmBtn.png").size());
//    //fmBtn->setContentsMargins(0, 0, 0, 0);

    mobileBtn = new QPushButton;
    mobileBtn->setFlat(true);
    mobileBtn->setFixedSize(50, 50);
    mobileBtn->setIcon(QPixmap(":/images/mobileIcon.png"));
    mobileBtn->setIconSize(QPixmap(":/images/mobileIcon.png").size());
    mobileBtn->setToolTip(tr("手机管理"));

    downloadBtn2 = new QPushButton;
    downloadBtn2->setFlat(true);
    downloadBtn2->setIcon(QPixmap(":/images/downloadIcon.png"));
    downloadBtn2->setIconSize(QPixmap(":/images/downloadIcon.png").size());
    downloadBtn2->setFixedSize(50, 50);
    downloadBtn2->setToolTip(tr("下载"));

    moreBtn = new QPushButton;
    moreBtn->setFlat(true);
    moreBtn->setFixedSize(50, 50);
    moreBtn->setIcon(QPixmap(":/images/moreIcon.png"));
    moreBtn->setIconSize(QPixmap(":/images/moreIcon.png").size());
    moreBtn->setToolTip(tr("更多"));

    packUpBtn = new QPushButton;
    packUpBtn->setFlat(true);
    packUpBtn->setFixedSize(50, 50);
    packUpBtn->setIcon(QPixmap(":/images/packup.png"));
    packUpBtn->setIconSize(QPixmap(":/images/packup.png").size());
    packUpBtn->setToolTip(tr("收起列表"));

    //添加上面这些按钮的事件关联，是的当点击按钮时，能够切换到相应的窗体
    //音乐列表按钮与堆栈窗体的第一个窗体管理
    connect(musicListBtn, SIGNAL(clicked()), this, SLOT(on_musicListBtn_clicked()));
    connect(favoriteBtn, SIGNAL(clicked()), this, SLOT(on_favoriteBtn_clicked()));
    connect(mobileBtn, SIGNAL(clicked()), this, SLOT(on_mobileBtn_clicked()));
    connect(downloadBtn2, SIGNAL(clicked()), this, SLOT(on_downloadBtn_clicked()));
    connect(moreBtn, SIGNAL(clicked()), this, SLOT(on_moreBtn_clicked()));
    connect(packUpBtn, SIGNAL(clicked()), this, SLOT(on_packUpBtn_clicked()));


    /***************************************************************************/
    //第一个小布局的布局QVBoxLayout
    secVLayout = new QVBoxLayout;
    //secVLayout->addWidget(secList);
    secVLayout->setSpacing(0);
    secVLayout->setMargin(0);
    //secVLayout->setSizeConstraint(QLayout::SetFixedSize);
    secVLayout->addWidget(musicListBtn);
    secVLayout->addWidget(favoriteBtn);
    //secVLayout->addWidget(fmBtn);
    secVLayout->addWidget(mobileBtn);
    secVLayout->addWidget(downloadBtn2);
    secVLayout->addWidget(moreBtn);
    secVLayout->addWidget(packUpBtn);
    secVLayout->addStretch();
    //secVLayout->setGeometry(QRect(QPoint(40, 40), QSize(40, this->geometry().height())));

    /****************************************************************************/
    //创建第二个小布局的QStackedWidget
    secStack = new QStackedWidget;
    //设置固定宽度
    secStack->setFixedWidth(300);
    //设置堆栈窗口的风格
    //secStacke->setFrameStyle(QFrame::Panel);

    //创建第二个小布局的元素并添加上去
    muList = new MusicList();
    faList = new FavoriteList();
    mobileWidget = new MobileManage();
    downloadWidget = new Download();
    moreWidget = new More();
    puWidget = new packUpWidget();
    secStack->addWidget(muList);
    secStack->addWidget(faList);
    secStack->addWidget(mobileWidget);
    secStack->addWidget(downloadWidget);
    secStack->addWidget(moreWidget);
    secStack->addWidget(puWidget);

    //将六个小窗体发送过来的可以播放的信号，传递给顶层的窗体

    connect(muList, SIGNAL(fromMusicListToSecFrame(SingleMusic*, bool)),
                    this, SLOT(OkSendToTop(SingleMusic *, bool)));

    connect(faList, SIGNAL(fromFavoriteToSecFrame(SingleMusic*, bool)),
                    this, SLOT(OkSendToTop(SingleMusic *, bool)));


    /******************************************************************************/
    //创建第三个小布局，也即搜索显示窗口那部分
    downloadDisplay = new DisplayWidget();

    //连接displaywidget的发送的播放歌曲的信号
    connect(downloadDisplay, SIGNAL(DWplayMusic(SingleMusic*,bool)),
            this, SLOT(OkSendToTop(SingleMusic*, bool)));
    //当有搜索结果时，就通知是否显示搜索结果页面
    connect(downloadDisplay, SIGNAL(okToShow(bool)),
            this, SLOT(okToShowDownload(bool)));

    //当单击了添加按钮之后，要将相应的歌曲添加到favorite窗体中的“试听音乐”列表中
    connect(downloadDisplay, SIGNAL(addThisMusicToListDis(SingleMusic*)),
            this, SLOT(addToFavoriteList(SingleMusic*)));

    //当没有搜索时，这个窗体时隐藏的，只有当有搜索结果时才显示出来
    downloadDisplay->hide();

    //空窗体，有第三小布局(也即搜索结果）时就隐藏，其他视乎就显示
    emptyWidget = new QWidget;
    emptyLayout = new QHBoxLayout(emptyWidget);
    emptyLayout->addStretch();

    //歌词显示窗体
    lyricWidget = new LyricWidget();



    //测试用，有歌词窗体之后就隐藏掉空窗体,
    //之后要修改完整，使得歌词窗体与搜索窗体进行切换
    emptyWidget->hide();



    /*****************************************************************************/
    //对主布局的完成
    secMainLayout->setMargin(0);
    secMainLayout->setSpacing(0);
    //添加第一个小布局
    secMainLayout->addLayout(secVLayout);
    //添加第二个小布局
    secMainLayout->addWidget(secStack);
    //添加第三个小布局
    secMainLayout->addWidget(downloadDisplay);
    secMainLayout->addWidget(emptyWidget);

    //添加歌词窗体
    secMainLayout->addWidget(lyricWidget);
    //secMainLayout->setStretch(0);


}

/*对于播放列表与收藏列表之间的切换是这样实现的：
 * 自定义了槽函数，当鼠标单击第一列中的按钮时，按钮的clicked()信号会连接上自定义的槽函数，
 * 而这个槽函数的实现内容就是令堆栈窗口重新设置当前索引，使得切换到按钮对应的那个窗口上
 */

void SecFrame::on_favoriteBtn_clicked()
{
    secStack->show();
    emit secStack->setCurrentIndex(1);

}

void SecFrame::on_musicListBtn_clicked()
{
    secStack->show();
    emit secStack->setCurrentIndex(0);

}

void SecFrame::on_mobileBtn_clicked()
{
    secStack->show();
    emit secStack->setCurrentIndex(2);

    //测试用，显示歌词窗体，之后删除
    showLyric();
}

void SecFrame::on_downloadBtn_clicked()
{
    secStack->show();
    emit secStack->setCurrentIndex(3);

    //测试用，显示搜索结果，之后删除
    showDisplay();
}

void SecFrame::on_moreBtn_clicked()
{
    secStack->show();
    emit secStack->setCurrentIndex(4);
}

void SecFrame::on_packUpBtn_clicked()
{
    emit secStack->setCurrentIndex(5);

    //连第二小布局都隐藏
    secStack->hide();

    //显示空窗体
    //showEmpty();
    //测试下全屏显示歌词
    showLyric();

//    //显示或隐藏空窗体及搜索结果显示窗体
//    closeDisplayWidget();
}

//接收从六个小窗体传递过来的可以播放信号，但这里要控制住，使得只能播放一首歌曲
void SecFrame::OkSendToTop(SingleMusic *sFmusic, bool bOk)
{
    OnlyMusic = sFmusic;

    //判断是从哪个界面传递过来的歌曲，选择性地进行播放，但试听界面的歌曲与本地音乐的播放
    //矛盾是在Widget窗体中解决的，增加了一个PreplayOrpauseMusic()函数来控制播放的唯一性！
    whichInterface();

    //将播放歌曲传递给最顶层的窗体
    emit SendToTop(OnlyMusic);
}


//显示或隐藏空窗体及搜索结果显示窗体
//void SecFrame::closeDisplayWidget()
//{
//    if(!okToShowDownloadBool)
//    {
//        //如果没有搜索，则不管怎样都是要显示空窗体的
//        emptyWidget->show();
//    }
//    else
//    {
//        //如果有搜索结果了，则要看点击按钮的情况,
//        if(okToShowEmptyWidget)
//        {
//            //如果允许你空窗体显示就显示空窗体，隐藏搜索结果窗体
//            emptyWidget->show();
//            downloadDisplay->hide();
//            //同时设置下次就隐藏空窗体，显示搜索结果窗体
//            okToShowEmptyWidget = false;
//        }
//        else
//        {
//            //如果不允许空窗体显示，就隐藏空窗体，显示搜索窗体
//            emptyWidget->hide();
//            downloadDisplay->show();
//            //同时设置下次就可以显示空窗体了
//            okToShowEmptyWidget = true;
//        }
//    }

//}

void SecFrame::okToShowDownload(bool )
{
//    okToShowDownloadBool = true;
//    //显示搜索结果的窗体
//    downloadDisplay->show();
//    //同时也要将空窗体隐藏
//    emptyWidget->hide();

    showDisplay();
}

void SecFrame::whichInterface()
{

    //emit closePrevMusic();
    //首先判断是从试听列表还是从本地音乐列表中传递过来的音乐
    if(!downloadDisplay->DWoktoplay)
    {
        //不是从试听界面传递过来的音乐

        //通过控制当前选中的索引号来控制另外一个窗体的所欲列表音乐都关闭
        if(secStack->currentIndex() == 0)
            faList->closeAllFavoriteList();
        else if(secStack->currentIndex() == 1)
            muList->closeAllMusicList();
        else
        {
        }   //什么都不做
    }
    else
    {
        //如果是从试听界面传递过来的歌曲，则关闭所有本地音乐的播放
        faList->closeAllFavoriteList();
        muList->closeAllMusicList();

    }
}

//单击了添加按钮后，将相应的歌曲添加到favoritelist中的“试听音乐”列表中
void SecFrame::addToFavoriteList(SingleMusic *addmus)
{

    faList->addMusicToList(addmus);
}

//只显示空窗体、歌词窗体、搜索显示窗体中的唯一个窗体
void SecFrame::showOnlyOneWidget()
{
    if(okToShowEmptyWidget)
    {
        //如果空窗体能够显示，则其它两个窗体就要关闭
        emptyWidget->show();
        downloadDisplay->hide();
        lyricWidget->hide();
        okToShowDownloadBool = false;
        okToShowLyric = false;
    }
    else
    {
        //如果空窗体没有显示，则显示剩下两个窗体中的一个
        if(okToShowDownloadBool)
        {
            //如果搜索结果窗体能够显示，则另两个窗体要关闭
            downloadDisplay->show();
            emptyWidget->hide();
            lyricWidget->hide();
            okToShowLyric = false;
        }
        else
        {
            //如果空窗体没有显示则显示歌词窗体，关闭其它两个窗体
            lyricWidget->show();
            downloadDisplay->hide();
            emptyWidget->hide();
            okToShowLyric = true;
        }
    }
}

//只显示歌词窗体
void SecFrame::showLyric()
{
    okToShowLyric = true;
    okToShowEmptyWidget = false;
    okToShowDownloadBool = false;
    showOnlyOneWidget();
}

//只显示搜索结果窗体
void SecFrame::showDisplay()
{

    okToShowDownloadBool = true;
    okToShowEmptyWidget = false;
    okToShowLyric = false;
    showOnlyOneWidget();

}

//只显示空窗体
void SecFrame::showEmpty()
{
    okToShowEmptyWidget = true;
    okToShowDownloadBool = false;
    okToShowLyric = false;
    showOnlyOneWidget();
}
