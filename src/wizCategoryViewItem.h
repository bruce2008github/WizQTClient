#ifndef WIZCATEGORYVIEWITEM_H
#define WIZCATEGORYVIEWITEM_H

#include <QTreeWidgetItem>

#include "share/wizobject.h"


class CWizDatabase;
class CWizExplorerApp;
class CWizCategoryBaseView;

class CWizCategoryViewItemBase : public QTreeWidgetItem
{
public:
    CWizCategoryViewItemBase(CWizExplorerApp& app, const QString& strName = "", const QString& strKbGUID = "");
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos) = 0;
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument) = 0;
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data) { Q_UNUSED(db); Q_UNUSED(data); return false; }
    virtual bool acceptDrop(const CWizCategoryViewItemBase* pItem) const { Q_UNUSED(pItem); return false;}
    virtual bool acceptDrop(const WIZDOCUMENTDATA& data) const { Q_UNUSED(data); return false; }
    virtual bool dragAble() const { return false; }
    virtual void drop(const WIZDOCUMENTDATA& data, bool forceCopy = false) { Q_UNUSED(data); Q_UNUSED(forceCopy);}

    virtual void draw(QPainter* p, const QStyleOptionViewItemV4* vopt) const;

    virtual QVariant data(int column, int role) const;
    virtual int getItemHeight(int hintHeight) const;
    virtual bool operator<(const QTreeWidgetItem &other) const;

    const QString& kbGUID() const { return m_strKbGUID; }
    const QString& name() const { return m_strName; }

    virtual QString id() const;

    void setDocumentsCount(int nCurrent, int nTotal);

    //
    virtual int getSortOrder() const { return 0; }

    //
    virtual QString getSectionName() { return QString(); }

    //Extra Button
    virtual void setExtraButtonIcon(const QString &file);
    virtual bool getExtraButtonIcon(QPixmap &ret) const;
    virtual QRect getExtraButtonRect(const QRect &itemBorder, bool ignoreIconExist = false) const;
    virtual bool extraButtonClickTest();

    //
    virtual QString countString() const { return m_countString; }

protected:
    CWizExplorerApp& m_app;
    QString m_strName;
    QString m_strKbGUID;
    QPixmap m_extraButtonIcon;
    QString m_countString;
};



class CWizCategoryViewSectionItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewSectionItem(CWizExplorerApp& app, const QString& strName, int sortOrder);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos) { Q_UNUSED(pCtrl); Q_UNUSED(pos); }
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument) { Q_UNUSED(db); Q_UNUSED(arrayDocument); }
    virtual int getItemHeight(int nHeight) const;
    virtual int getSortOrder() const { return m_sortOrder; }
    void reset(const QString& sectionName, int sortOrder);

    virtual QRect getExtraButtonRect(const QRect &itemBorder, bool ignoreIconExist = false) const;
    virtual void draw(QPainter* p, const QStyleOptionViewItemV4* vopt) const;
protected:
    int m_sortOrder;
};

class CWizCategoryViewMessageItem : public CWizCategoryViewItemBase
{
public:
    enum FilterType {
        All,
        SendToMe,
        ModifyNote,
        Comment,
        SendFromMe
    };

    CWizCategoryViewMessageItem(CWizExplorerApp& app, const QString& strName, int nFilter);
    virtual void draw(QPainter* p, const QStyleOptionViewItemV4 *vopt) const;

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos)
    { Q_UNUSED(pCtrl); Q_UNUSED(pos); }

    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument)
    { Q_UNUSED(db); Q_UNUSED(arrayDocument); }

    void getMessages(CWizDatabase& db, CWizMessageDataArray& arrayMsg);
    void setUnreadCount(int nCount);
    QString unreadString() const;
    bool hitTestUnread();

    virtual QString getSectionName();
    virtual int getSortOrder() const { return 10; }


private:
    int m_nFilter;
    int m_nUnread;
    QSize m_szUnreadSize;
};

class CWizCategoryViewShortcutRootItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewShortcutRootItem(CWizExplorerApp& app, const QString& strName);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos)
    { Q_UNUSED(pCtrl); Q_UNUSED(pos); }

    virtual void getDocuments(CWizDatabase& db,
                              CWizDocumentDataArray& arrayDocument);

    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual void drop(const WIZDOCUMENTDATA& data, bool forceCopy = false);
    virtual bool acceptDrop(const WIZDOCUMENTDATA& /*data*/) const {return true;}

    virtual QString getSectionName();
    virtual int getSortOrder() const { return 11; }

    void addPlaceHoldItem();
    bool isContainsPlaceHoldItem();
    void removePlaceHoldItem();
};

class CWizCategoryViewShortcutPlaceHoldItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewShortcutPlaceHoldItem(CWizExplorerApp& app, const QString& strName);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos) {}
    virtual void getDocuments(CWizDatabase& db,
                              CWizDocumentDataArray& arrayDocument)
    { Q_UNUSED(db); Q_UNUSED(arrayDocument); }
};

class CWizCategoryViewShortcutItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewShortcutItem(CWizExplorerApp& app, const QString& strName,
                                 const QString& strKbGuid, const QString& strGuid, bool bEncrypted = false);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    virtual void getDocuments(CWizDatabase& db,
                              CWizDocumentDataArray& arrayDocument)
    { Q_UNUSED(db); Q_UNUSED(arrayDocument); }

    QString guid() {return m_strGuid;}

private:
    QString m_strGuid;
};

class CWizCategoryViewSearchRootItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewSearchRootItem(CWizExplorerApp& app, const QString& strName);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos)
    { Q_UNUSED(pCtrl); Q_UNUSED(pos); }

    virtual void getDocuments(CWizDatabase& db,
                              CWizDocumentDataArray& arrayDocument)
    { Q_UNUSED(db); Q_UNUSED(arrayDocument); }
};

class CWizCategoryViewAllFoldersItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewAllFoldersItem(CWizExplorerApp& app, const QString& strName, const QString& strKbGUID);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual bool acceptDrop(const CWizCategoryViewItemBase* pItem) const;
    virtual QString getSectionName();
    virtual int getSortOrder() const { return 20; }
};

class CWizCategoryViewFolderItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewFolderItem(CWizExplorerApp& app, const QString& strLocation, const QString& strKbGUID);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual bool acceptDrop(const WIZDOCUMENTDATA& data) const;
    virtual bool acceptDrop(const CWizCategoryViewItemBase* pItem) const;
    virtual bool dragAble() const { return true; }
    virtual void drop(const WIZDOCUMENTDATA& data, bool forceCopy = false);

    virtual bool operator < (const QTreeWidgetItem &other) const;

    virtual QTreeWidgetItem* clone() const;

    virtual QString id() const;

    QString location() const { return m_strName; }
    void setLocation(const QString& strLocation);
    QString name() const;

private:
    QRect m_rcUnread;
};

class CWizCategoryViewAllTagsItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewAllTagsItem(CWizExplorerApp& app, const QString& strName, const QString& strKbGUID);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual bool acceptDrop(const CWizCategoryViewItemBase* pItem) const;
    virtual QString getSectionName();
    virtual int getSortOrder() const { return 21; }
};

class CWizCategoryViewTagItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewTagItem(CWizExplorerApp& app, const WIZTAGDATA& tag, const QString& strKbGUID);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual bool acceptDrop(const WIZDOCUMENTDATA& data) const;
    virtual void drop(const WIZDOCUMENTDATA& data, bool forceCopy = false);

    virtual QTreeWidgetItem *clone() const;

    void reload(CWizDatabase& db);
    void setTagPosition(int nPos);
    const WIZTAGDATA& tag() const { return m_tag; }

private:
    WIZTAGDATA m_tag;
};

class CWizCategoryViewStyleRootItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewStyleRootItem(CWizExplorerApp& app, const QString& strName);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos)
    { Q_UNUSED(pCtrl); Q_UNUSED(pos); }

    virtual void getDocuments(CWizDatabase& db,
                              CWizDocumentDataArray& arrayDocument)
    { Q_UNUSED(db); Q_UNUSED(arrayDocument); }
    virtual QString getSectionName();
    virtual int getSortOrder() const { return 22; }
};

class CWizCategoryViewGroupsRootItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewGroupsRootItem(CWizExplorerApp& app, const QString& strName);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);

    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual bool acceptDrop(const CWizCategoryViewItemBase* pItem) const;
    virtual QString getSectionName();

};

class CWizCategoryViewBizGroupRootItem : public CWizCategoryViewGroupsRootItem
{
public:
    CWizCategoryViewBizGroupRootItem(CWizExplorerApp& app,
                                     const WIZBIZDATA& biz);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    //
    const WIZBIZDATA biz() const { return m_biz; }
    virtual int getSortOrder() const { return 30; }    
    //
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual void draw(QPainter* p, const QStyleOptionViewItemV4* vopt) const;
    //
    bool isExtraButtonUseable();
    bool isUnreadButtonUseable() const;
    void updateUnreadCount();
    QString unreadString() const;
    bool hitTestUnread();
    //
    bool isOwner();
    bool isAdmin();
    bool isHr();


private:
    WIZBIZDATA m_biz;
    int m_unReadCount;
    QSize m_szUnreadSize;
    bool m_extraButtonUseable;
};
class CWizCategoryViewOwnGroupRootItem : public CWizCategoryViewGroupsRootItem
{
public:
    CWizCategoryViewOwnGroupRootItem(CWizExplorerApp& app);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);

    virtual int getSortOrder() const { return 31; }
};

class CWizCategoryViewJionedGroupRootItem : public CWizCategoryViewGroupsRootItem
{
public:
    CWizCategoryViewJionedGroupRootItem(CWizExplorerApp& app);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos)
    { Q_UNUSED(pCtrl); Q_UNUSED(pos); }

    virtual int getSortOrder() const { return 32; }
};

class CWizCategoryViewLinkItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewLinkItem(CWizExplorerApp& app, const QString& strName, int commandId)
        : CWizCategoryViewItemBase(app, strName)
        , m_commandId(commandId) { setFlags(Qt::NoItemFlags); setText(0, strName); }

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos)
    { Q_UNUSED(pCtrl); Q_UNUSED(pos); }
    virtual void getDocuments(CWizDatabase& db,
                              CWizDocumentDataArray& arrayDocument)
    { Q_UNUSED(db); Q_UNUSED(arrayDocument); }
    int commandId() const { return m_commandId; }
protected:
    int m_commandId;
};

class CWizCategoryViewCreateGroupLinkItem : public CWizCategoryViewLinkItem
{
public:
    CWizCategoryViewCreateGroupLinkItem(CWizExplorerApp& app, const QString& strName, int commandId)
        : CWizCategoryViewLinkItem(app, strName, commandId) {}
    //
    virtual QString getSectionName();
    virtual int getSortOrder() const { return 33; }


};


class CWizCategoryViewGroupRootItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewGroupRootItem(CWizExplorerApp& app,
                                  const WIZGROUPDATA& group);

    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual bool acceptDrop(const WIZDOCUMENTDATA& data) const;
    virtual bool acceptDrop(const CWizCategoryViewItemBase* pItem) const;
    virtual void drop(const WIZDOCUMENTDATA& data, bool forceCopy = false);
    virtual void draw(QPainter* p, const QStyleOptionViewItemV4* vopt) const;
    void reload(CWizDatabase& db);
    //
    bool isAdmin(CWizDatabase& db);
    bool isOwner(CWizDatabase& db);

    bool isBizGroup() const;
    QString bizGUID() const;
    //
    void setUnreadCount(int nCount);
    int getUnreadCount();
    QString unreadString() const;
    bool hitTestUnread();

private:
    WIZGROUPDATA m_group;
    int m_nUnread;
    QSize m_szUnreadSize;
};

class CWizCategoryViewGroupNoTagItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewGroupNoTagItem(CWizExplorerApp& app, const QString& strKbGUID);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos) {Q_UNUSED(pCtrl); Q_UNUSED(pos);}
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual int getSortOrder() const { return 10; }
};

class CWizCategoryViewGroupItem : public CWizCategoryViewItemBase
{
public:
    CWizCategoryViewGroupItem(CWizExplorerApp& app, const WIZTAGDATA& tag, const QString& strKbGUID);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual bool acceptDrop(const WIZDOCUMENTDATA& data) const;
    virtual bool dragAble() const { return true; }
    virtual void drop(const WIZDOCUMENTDATA& data, bool forceCopy = false);

    virtual QString id() const;

    virtual bool operator<(const QTreeWidgetItem &other) const;

    void reload(CWizDatabase& db);
    void setTagPosition(int nPos);
    const WIZTAGDATA& tag() const { return m_tag; }

    virtual int getSortOrder() const { return 11; }

private:
    WIZTAGDATA m_tag;
};

class CWizCategoryViewTrashItem : public CWizCategoryViewFolderItem
{
public:
    CWizCategoryViewTrashItem(CWizExplorerApp& app, const QString& strKbGUID);
    virtual void showContextMenu(CWizCategoryBaseView* pCtrl, QPoint pos);
    virtual void getDocuments(CWizDatabase& db, CWizDocumentDataArray& arrayDocument);
    virtual bool accept(CWizDatabase& db, const WIZDOCUMENTDATA& data);
    virtual bool acceptDrop(const WIZDOCUMENTDATA& data) const;
    virtual bool acceptDrop(const CWizCategoryViewItemBase* pItem) const;
    virtual bool dragAble() const { return false; }
    virtual int getSortOrder() const { return 12; }
};

#endif // WIZCATEGORYVIEWITEM_H
