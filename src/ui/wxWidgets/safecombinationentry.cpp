/*
 * Copyright (c) 2003-2015 Rony Shapiro <ronys@users.sourceforge.net>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License 2.0 terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 */

/** \file safecombinationentry.cpp
*
*/
// Generated by DialogBlocks, Sun 18 Jan 2009 09:22:13 PM IST

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "SafeCombinationCtrl.h"
////@end includes

#include <wx/timer.h>
#include "safecombinationentry.h"
#include "safecombinationsetup.h"
#include "version.h"
#include "core/core.h"
#include "core/PWSdirs.h"
#include "os/file.h"

#ifndef NO_YUBI
////@begin XPM images
#include "graphics/Yubikey-button.xpm"
////@end XPM images
#endif

#include "./graphics/cpane.xpm"
#include "./graphics/psafetxt.xpm"
#include "pwsafeapp.h"
#include <wx/filename.h>

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>
#endif

#include <iostream> // for debugging
#include <iomanip>

/*!
 * CSafeCombinationEntry type definition
 */

IMPLEMENT_CLASS( CSafeCombinationEntry, wxDialog )


/*!
 * CSafeCombinationEntry event table definition
 */

BEGIN_EVENT_TABLE( CSafeCombinationEntry, wxDialog )

////@begin CSafeCombinationEntry event table entries
  EVT_ACTIVATE( CSafeCombinationEntry::OnActivate )

  EVT_BUTTON( ID_ELLIPSIS, CSafeCombinationEntry::OnEllipsisClick )

  EVT_BUTTON( ID_NEWDB, CSafeCombinationEntry::OnNewDbClick )

#ifndef NO_YUBI
  EVT_BUTTON( ID_YUBIBTN, CSafeCombinationEntry::OnYubibtnClick )

  EVT_TIMER(POLLING_TIMER_ID, CSafeCombinationEntry::OnPollingTimer)
#endif

  EVT_BUTTON( wxID_OK, CSafeCombinationEntry::OnOk )

  EVT_BUTTON( wxID_CANCEL, CSafeCombinationEntry::OnCancel )

  EVT_COMBOBOX(ID_DBASECOMBOBOX, CSafeCombinationEntry::OnDBSelectionChange)
////@end CSafeCombinationEntry event table entries
END_EVENT_TABLE()


/*!
 * CSafeCombinationEntry constructors
 */

CSafeCombinationEntry::CSafeCombinationEntry(PWScore &core)
: m_core(core), m_tries(0)
{
  Init();
}

CSafeCombinationEntry::CSafeCombinationEntry(wxWindow* parent, PWScore &core,
                                             wxWindowID id,
                                             const wxString& caption,
                                             const wxPoint& pos,
                                             const wxSize& size, long style)
  : m_core(core), m_tries(0)
{
  Init();
  Create(parent, id, caption, pos, size, style);
}


/*!
 * CSafeCombinationEntry creator
 */

bool CSafeCombinationEntry::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CSafeCombinationEntry creation
  SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
  wxDialog::Create( parent, id, caption, pos, size, style );

  CreateControls();
  if (GetSizer())
  {
    GetSizer()->SetSizeHints(this);
  }
  Centre();
////@end CSafeCombinationEntry creation
#ifndef NO_YUBI
  SetupMixin(FindWindow(ID_YUBIBTN), FindWindow(ID_YUBISTATUS));
  m_pollingTimer = new wxTimer(this, POLLING_TIMER_ID);
  m_pollingTimer->Start(CYubiMixin::POLLING_INTERVAL);
#endif
  return true;
}


/*!
 * CSafeCombinationEntry destructor
 */

CSafeCombinationEntry::~CSafeCombinationEntry()
{
////@begin CSafeCombinationEntry destruction
////@end CSafeCombinationEntry destruction
#ifndef NO_YUBI
  delete m_pollingTimer;
#endif
}


/*!
 * Member initialisation
 */

void CSafeCombinationEntry::Init()
{
  m_readOnly = m_core.IsReadOnly();
  m_filename = m_core.GetCurFile().c_str();
////@begin CSafeCombinationEntry member initialisation
  m_version = NULL;
  m_filenameCB = NULL;
  m_combinationEntry = NULL;
#ifndef NO_YUBI
  m_YubiBtn = NULL;
  m_yubiStatusCtrl = NULL;
#endif
  m_postInitDone = false;
////@end CSafeCombinationEntry member initialisation
}


/*!
 * Control creation for CSafeCombinationEntry
 */

void CSafeCombinationEntry::CreateControls()
{
////@begin CSafeCombinationEntry content construction
  CSafeCombinationEntry* itemDialog1 = this;

  wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
  itemDialog1->SetSizer(itemBoxSizer2);

  wxStaticBitmap* itemStaticBitmap3 = new wxStaticBitmap( itemDialog1, wxID_STATIC, itemDialog1->GetBitmapResource(wxT("graphics/cpane.xpm")), wxDefaultPosition, itemDialog1->ConvertDialogToPixels(wxSize(49, 46)), 0 );
  itemBoxSizer2->Add(itemStaticBitmap3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
  itemBoxSizer2->Add(itemBoxSizer4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

  wxStaticBitmap* itemStaticBitmap6 = new wxStaticBitmap( itemDialog1, wxID_STATIC, itemDialog1->GetBitmapResource(wxT("graphics/psafetxt.xpm")), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer5->Add(itemStaticBitmap6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  m_version = new wxStaticText( itemDialog1, wxID_STATIC, _("VX.YY"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer5->Add(m_version, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("Open Password Database:"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer4->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALL, 3);

  wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer9, 50, wxGROW|wxALL, 5);

  wxArrayString m_filenameCBStrings;
  m_filenameCB = new wxComboBox( itemDialog1, ID_DBASECOMBOBOX, wxEmptyString, wxDefaultPosition, wxSize(itemDialog1->ConvertDialogToPixels(wxSize(140, -1)).x, -1), m_filenameCBStrings, wxCB_DROPDOWN );
  itemBoxSizer9->Add(m_filenameCB, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 0);

  wxButton* itemButton11 = new wxButton( itemDialog1, ID_ELLIPSIS, wxT("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
  itemBoxSizer9->Add(itemButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _("Safe Combination:"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer4->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALL, 3);

  m_combinationEntry = new CSafeCombinationCtrl( itemDialog1, ID_COMBINATION, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer4->Add(m_combinationEntry, 0, wxGROW|wxRIGHT|wxTOP|wxBOTTOM, 5);

  wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer14, 0, wxGROW|wxALL, 5);

  wxCheckBox* itemCheckBox15 = new wxCheckBox( itemDialog1, ID_READONLY, _("Open as read-only"), wxDefaultPosition, wxDefaultSize, 0 );
  itemCheckBox15->SetValue(false);
  itemBoxSizer14->Add(itemCheckBox15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

  itemBoxSizer14->Add(120, 10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

  wxButton* itemButton17 = new wxButton( itemDialog1, ID_NEWDB, _("New..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
  itemBoxSizer14->Add(itemButton17, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP|wxBOTTOM, 5);

  wxBoxSizer* itemBoxSizer18 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer4->Add(itemBoxSizer18, 0, wxGROW|wxALL, 5);

#ifndef NO_YUBI
  m_YubiBtn = new wxBitmapButton( itemDialog1, ID_YUBIBTN, itemDialog1->GetBitmapResource(wxT("graphics/Yubikey-button.xpm")), wxDefaultPosition, itemDialog1->ConvertDialogToPixels(wxSize(40, 15)), wxBU_AUTODRAW );
  itemBoxSizer18->Add(m_YubiBtn, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM|wxSHAPED, 5);

  m_yubiStatusCtrl = new wxStaticText( itemDialog1, ID_YUBISTATUS, _("Please insert your YubiKey"), wxDefaultPosition, wxDefaultSize, 0 );
  itemBoxSizer18->Add(m_yubiStatusCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
#endif

  wxStdDialogButtonSizer* itemStdDialogButtonSizer21 = new wxStdDialogButtonSizer;

  itemBoxSizer4->Add(itemStdDialogButtonSizer21, 0, wxGROW|wxALL, 0);
  wxButton* itemButton22 = new wxButton( itemDialog1, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
  itemButton22->SetDefault();
  itemStdDialogButtonSizer21->AddButton(itemButton22);

  wxButton* itemButton23 = new wxButton( itemDialog1, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer21->AddButton(itemButton23);

  wxButton* itemButton24 = new wxButton( itemDialog1, wxID_HELP, _("&Help"), wxDefaultPosition, wxDefaultSize, 0 );
  itemStdDialogButtonSizer21->AddButton(itemButton24);

  itemStdDialogButtonSizer21->Realize();

  // Set validators
  m_filenameCB->SetValidator( wxGenericValidator(& m_filename) );
  itemCheckBox15->SetValidator( wxGenericValidator(& m_readOnly) );
////@end CSafeCombinationEntry content construction
  m_combinationEntry->SetValidatorTarget(& m_password);

#if (REVISION == 0)
  m_version->SetLabel(wxString::Format(wxT("V%d.%d %ls"),
                                       MAJORVERSION, MINORVERSION, SPECIALBUILD));
#else
  m_version->SetLabel(wxString::Format(wxT("V%d.%d.%d %ls"),
                                       MAJORVERSION, MINORVERSION,
                                       REVISION, SPECIALBUILD));
#endif
  wxArrayString recentFiles;
  wxGetApp().recentDatabases().GetAll(recentFiles);
  m_filenameCB->Append(recentFiles);
  // The underlying native combobox widget might not yet be ready
  //  to hand back the string we just added
  wxCommandEvent cmdEvent(wxEVT_COMMAND_COMBOBOX_SELECTED, m_filenameCB->GetId());
  GetEventHandler()->AddPendingEvent(cmdEvent);
  SetIcons(wxGetApp().GetAppIcons());
}

void CSafeCombinationEntry::OnActivate( wxActivateEvent& event )
{
  if (!m_postInitDone) {
    // if filename field not empty, set focus to password:
    if (!m_filename.empty()) {
      FindWindow(ID_COMBINATION)->SetFocus();
    }
    m_postInitDone = true;
  }
}

/*!
 * Should we show tooltips?
 */

bool CSafeCombinationEntry::ShowToolTips()
{
  return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap CSafeCombinationEntry::GetBitmapResource( const wxString& name )
{
  // Bitmap retrieval
////@begin CSafeCombinationEntry bitmap retrieval
  if (name == _T("graphics/cpane.xpm"))
  {
    wxBitmap bitmap(cpane_xpm);
    return bitmap;
  }
  else if (name == _T("graphics/psafetxt.xpm"))
  {
    wxBitmap bitmap(psafetxt_xpm);
    return bitmap;
  }
#ifndef NO_YUBI
  else if (name == _T("graphics/Yubikey-button.xpm"))
  {
    wxBitmap bitmap(Yubikey_button_xpm);
    return bitmap;
  }
#endif
  return wxNullBitmap;
////@end CSafeCombinationEntry bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon CSafeCombinationEntry::GetIconResource( const wxString& WXUNUSED(name) )
{
  // Icon retrieval
////@begin CSafeCombinationEntry icon retrieval
  return wxNullIcon;
////@end CSafeCombinationEntry icon retrieval
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
 */

void CSafeCombinationEntry::OnOk( wxCommandEvent& )
{
  if (Validate() && TransferDataFromWindow()) {
    if (m_password.empty()) {
      wxMessageDialog err(this, _("The combination cannot be blank."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      FindWindow(ID_COMBINATION)->SetFocus();
      return;
    }
    if (!pws_os::FileExists(tostdstring(m_filename))) {
      wxMessageDialog err(this, _("File or path not found."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      m_filenameCB->SetFocus();
      return;
    }
    ProcessPhrase();
  } // Validate && TransferDataFromWindow
}

void CSafeCombinationEntry::ProcessPhrase()
{
  int status = m_core.CheckPasskey(tostringx(m_filename), m_password);
  wxString errmess;
  switch (status) {
  case PWScore::SUCCESS:
    m_core.SetReadOnly(m_readOnly);
    m_core.SetCurFile(tostringx(m_filename));
    wxGetApp().recentDatabases().AddFileToHistory(m_filename);
    EndModal(wxID_OK);
    return;
  case PWScore::CANT_OPEN_FILE:
    { stringT str;
      LoadAString(str, IDSC_FILE_UNREADABLE);
      errmess = str.c_str();
    }
    break;
  case PWScore::WRONG_PASSWORD:
  default:
    if (m_tries >= 2) {
      errmess = _("Three strikes - yer out!");
    } else {
      m_tries++;
      errmess = _("Incorrect passkey, not a PasswordSafe database, or a corrupt database. (Backup database has same name as original, ending with '~')");
    }
    break;
  } // switch (status)
    // here iff CheckPasskey failed.
  wxMessageDialog err(this, errmess,
                      _("Error"), wxOK | wxICON_EXCLAMATION);
  err.ShowModal();
  wxTextCtrl *txt = (wxTextCtrl *)FindWindow(ID_COMBINATION);
  txt->SetSelection(-1,-1);
  txt->SetFocus();
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void CSafeCombinationEntry::OnCancel( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in CSafeCombinationEntry.
  // Before editing this code, remove the block markers.
  event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL in CSafeCombinationEntry.
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_ELLIPSIS
 */

void CSafeCombinationEntry::OnEllipsisClick( wxCommandEvent& /* evt */ )
{
  wxFileDialog fd(this, _("Please Choose a Database to Open:"),
                  PWSdirs::GetSafeDir().c_str(), wxT(""),
                  _("Password Safe Databases (*.psafe4; *.psafe3; *.dat)|*.psafe4;*.psafe3;*.dat| All files (*.*; *)|*.*;*"),
                  (wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR));

  if (fd.ShowModal() == wxID_OK) {
    m_filename = fd.GetPath();
    wxComboBox *cb = dynamic_cast<wxComboBox *>(FindWindow(ID_DBASECOMBOBOX));
    cb->SetValue(m_filename);
    UpdateReadOnlyCheckbox();
  }
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_NEWDB
 */

void CSafeCombinationEntry::OnNewDbClick( wxCommandEvent& /* evt */ )
{
  // 1. Get a filename from a file dialog box
  // 2. Get a password
  // 3. Set m_filespec && m_passkey to returned value!
  wxString newfile;
  wxString cs_msg, cs_title, cs_temp;

  wxString cf(wxT("pwsafe")); // reasonable default for first time user
  stringT v3FileName = PWSUtil::GetNewFileName(tostdstring(cf), wxT("psafe3"));
  stringT dir = PWSdirs::GetSafeDir();

  while (1) {
    wxFileDialog fd(this, _("Please choose a name for the new database"),
                    dir.c_str(), v3FileName.c_str(),
                    _("Password Safe Databases (*.psafe3; *.dat)|*.psafe3;*.dat| All files (*.*; *)|*.*;*"),
                  (wxFD_SAVE | wxFD_OVERWRITE_PROMPT| wxFD_CHANGE_DIR));
    int rc = fd.ShowModal();
    if (rc == wxID_OK) {
      wxFileName wxfn(fd.GetPath());
      if (wxfn.GetExt().empty()) {
        wxfn.SetExt(DEFAULT_SUFFIX);
      }
      newfile = wxfn.GetFullPath();
      break;
    } else
      return;
  }
  // 2. Get a password
  CSafeCombinationSetup pksetup(this);
  int rc = pksetup.ShowModal();

  if (rc != wxID_OK)
    return;  //User cancelled password entry

  // 3. Set m_filespec && m_passkey to returned value!
  m_core.SetCurFile(tostringx(newfile));

  // Now lock the new file
  std::wstring locker(L""); // null init is important here
  m_core.LockFile(tostdstring(newfile), locker);

  m_core.SetReadOnly(false); // new file can't be read-only...
  m_core.NewFile(tostringx(pksetup.GetPassword()));
  if ((rc = m_core.WriteCurFile()) == PWSfile::SUCCESS) {
    wxGetApp().recentDatabases().AddFileToHistory(newfile);
    EndModal(wxID_OK);
  }
  else {
    wxMessageBox(wxString()<< newfile << wxT("\n\n") << _("Could not open file for writing!"),
                 _("Write Error"), wxOK | wxICON_ERROR, this);
  }
}


#ifndef NO_YUBI
/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_YUBIBTN
 */

void CSafeCombinationEntry::OnYubibtnClick( wxCommandEvent& /* event */ )
{
  m_combinationEntry->AllowEmptyCombinationOnce();  // Allow blank password when Yubi's used

  if (Validate() && TransferDataFromWindow()) {
    if (!pws_os::FileExists(tostdstring(m_filename))) {
      wxMessageDialog err(this, _("File or path not found."),
                          _("Error"), wxOK | wxICON_EXCLAMATION);
      err.ShowModal();
      m_filenameCB->SetFocus();
      return;
    }

    StringX response;
    bool oldYubiChallenge = ::wxGetKeyState(WXK_SHIFT); // for pre-0.94 databases
    if (PerformChallengeResponse(this, m_password, response, oldYubiChallenge)) {
      m_password = response;
      ProcessPhrase();
      UpdateStatus();
    }
  }
}

void CSafeCombinationEntry::OnPollingTimer(wxTimerEvent &evt)
{
  if (evt.GetId() == POLLING_TIMER_ID) {
    HandlePollingTimer(); // in CYubiMixin
  }
}
#endif

void CSafeCombinationEntry::OnDBSelectionChange( wxCommandEvent& /*event*/ )
{
  UpdateReadOnlyCheckbox();
}

void CSafeCombinationEntry::UpdateReadOnlyCheckbox()
{
  wxFileName fn(m_filenameCB->GetValue());

  // Do nothing if the file doesn't exist
  if ( fn.FileExists() ) {
    const bool writeable = fn.IsFileWritable();
    wxCheckBox *ro = wxDynamicCast(FindWindow(ID_READONLY), wxCheckBox);
    ro->SetValue( writeable? m_core.IsReadOnly(): true );
    ro->Enable(writeable);
  }
}
