/*
 * Copyright (c) 2003-2009 Rony Shapiro <ronys@users.sourceforge.net>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License 2.0 terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 */

/** \file passwordsafeframe.h
 * 
 */

// Generated by DialogBlocks, Wed 14 Jan 2009 10:24:11 PM IST

#ifndef _PASSWORDSAFEFRAME_H_
#define _PASSWORDSAFEFRAME_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
////@end includes
#include "../../corelib/PWScore.h"

/*!
 * Forward declarations
 */

////@begin forward declarations
class PWSGrid;
class PWSTreeCtrl;
class PasswordSafeSearch;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_PASSWORDSAFEFRAME 10001
#define ID_MENU_CLEAR_MRU 10011
#define ID_EXPORTMENU 10013
#define ID_EXPORT2OLD1XFORMAT 10013
#define ID_EXPORT2V2FORMAT 10014
#define ID_EXPORT2PLAINTEXT 10015
#define ID_EXPORT2XML 10016
#define ID_IMPORTMENU 10017
#define ID_IMPORT_PLAINTEXT 10018
#define ID_IMPORT_XML 10019
#define ID_IMPORT_KEEPASS 10020
#define ID_MERGE 10021
#define ID_COMPARE 10022
#define ID_EDIT 10023
#define ID_RENAME 10024
#define ID_DUPLICATEENTRY 10025
#define ID_ADDGROUP 10026
#define ID_CLEARCLIPBOARD 10027
#define ID_COPYPASSWORD 10028
#define ID_COPYUSERNAME 10029
#define ID_COPYNOTESFLD 10030
#define ID_COPYURL 10031
#define ID_BROWSEURL 10032
#define ID_AUTOTYPE 10033
#define ID_GOTOBASEENTRY 10034
#define ID_LIST_VIEW 10035
#define ID_TREE_VIEW 10036
#define ID_SHOWHIDE_TOOLBAR 10037
#define ID_SHOWHIDE_DRAGBAR 10038
#define ID_EXPANDALL 10039
#define ID_COLLAPESALL 10040
#define ID_FILTERMENU 10041
#define ID_EDITFILTER 10042
#define ID_APPLYFILTER 10043
#define ID_MANAGEFILTERS 10044
#define ID_CUSTOMIZETOOLBAR 10045
#define ID_CHANGEFONTMENU 10046
#define ID_CHANGETREEFONT 10047
#define ID_CHANGEPSWDFONT 10048
#define ID_REPORTSMENU 10049
#define ID_REPORT_COMPARE 10050
#define ID_REPORT_FIND 10051
#define ID_REPORT_IMPORTTEXT 10052
#define ID_REPORT_IMPORTXML 10053
#define ID_REPORT_MERGE 10054
#define ID_REPORT_VALIDATE 10055
#define ID_CHANGECOMBO 10056
#define ID_BACKUP 10057
#define ID_RESTORE 10058
#define ID_OPTIONS 10059
#define ID_EDITMENU_FIND_NEXT 10060
#define ID_EDITMENU_FIND_PREVIOUS 10061
#define ID_MENUITEM 10012
#define SYMBOL_PASSWORDSAFEFRAME_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX
#define SYMBOL_PASSWORDSAFEFRAME_TITLE _("PasswordSafe")
#define SYMBOL_PASSWORDSAFEFRAME_IDNAME ID_PASSWORDSAFEFRAME
#define SYMBOL_PASSWORDSAFEFRAME_SIZE wxSize(400, 300)
#define SYMBOL_PASSWORDSAFEFRAME_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * PasswordSafeFrame class declaration
 */

class PasswordSafeFrame: public wxFrame
{    
    DECLARE_CLASS( PasswordSafeFrame )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    PasswordSafeFrame(PWScore &core);
    PasswordSafeFrame(wxWindow* parent, PWScore &core,
                      wxWindowID id = SYMBOL_PASSWORDSAFEFRAME_IDNAME, const wxString& caption = SYMBOL_PASSWORDSAFEFRAME_TITLE, const wxPoint& pos = SYMBOL_PASSWORDSAFEFRAME_POSITION, const wxSize& size = SYMBOL_PASSWORDSAFEFRAME_SIZE, long style = SYMBOL_PASSWORDSAFEFRAME_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PASSWORDSAFEFRAME_IDNAME, const wxString& caption = SYMBOL_PASSWORDSAFEFRAME_TITLE, const wxPoint& pos = SYMBOL_PASSWORDSAFEFRAME_POSITION, const wxSize& size = SYMBOL_PASSWORDSAFEFRAME_SIZE, long style = SYMBOL_PASSWORDSAFEFRAME_STYLE );

    /// Destructor
    ~PasswordSafeFrame();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    ItemList::size_type GetNumEntries() const {return m_core.GetNumEntries();}
    
////@begin PasswordSafeFrame event handler declarations

  /// wxEVT_CLOSE_WINDOW event handler for ID_PASSWORDSAFEFRAME
  void OnCloseWindow( wxCloseEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_OPEN
  void OnOpenClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_CLOSE
  void OnCloseClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_SAVE
  void OnSaveClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_PROPERTIES
  void OnPropertiesClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_EXIT
  void OnExitClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_ADD
  void OnAddClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_EDIT
  void OnEditClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_DELETE
  void OnDeleteClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxEVT_FIND
  void OnFindClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_EDITMENU_FIND_NEXT
  void OnFindNext(wxCommandEvent& evt);

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_EDITMENU_FIND_PREVIOUS
  void OnFindPrevious(wxCommandEvent& evt);

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_CLEARCLIPBOARD
  void OnClearclipboardClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_COPYPASSWORD
  void OnCopypasswordClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_COPYUSERNAME
  void OnCopyusernameClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_COPYNOTESFLD
  void OnCopynotesfldClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_COPYURL
  void OnCopyurlClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_LIST_VIEW
  void OnListViewClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_TREE_VIEW
  void OnTreeViewClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_CHANGECOMBO
  void OnChangePasswdClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for ID_OPTIONS
  void OnOptionsClick( wxCommandEvent& event );

  /// wxEVT_COMMAND_MENU_SELECTED event handler for wxID_ABOUT
  void OnAboutClick( wxCommandEvent& event );

////@end PasswordSafeFrame event handler declarations

////@begin PasswordSafeFrame member function declarations

  /// Retrieves bitmap resources
  wxBitmap GetBitmapResource( const wxString& name );

  /// Retrieves icon resources
  wxIcon GetIconResource( const wxString& name );
////@end PasswordSafeFrame member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    // Overriden virtuals
    virtual bool Show(bool show = true);
    virtual void SetTitle(const wxString& title);
    
    // PasswordSafe specifics:
    int Load(const wxString &passwd);
    
    // Hilites the item.  Used for search
    void SeletItem(const CUUIDGen& uuid);

    ItemListConstIter GetEntryIter() const { return m_core.GetEntryIter(); }
    ItemListConstIter GetEntryEndIter() const { return m_core.GetEntryEndIter(); }

////@begin PasswordSafeFrame member variables
  PWSGrid* m_grid;
  PWSTreeCtrl* m_tree;
////@end PasswordSafeFrame member variables
 private:
  int Open(const wxString &fname); // prompt for password, try to Load.
  int SaveIfChanged();
  int Save();
  void ShowGrid(bool show = true);
  void ShowTree(bool show = true);
  void ClearData();
  void Delete(const uuid_array_t &uuid);
  PWScore &m_core;
  enum {TREE, GRID} m_currentView;
  const CItemData *GetSelectedEntry() const;
  
  PasswordSafeSearch* m_search;

};

#endif
    // _PASSWORDSAFEFRAME_H_
