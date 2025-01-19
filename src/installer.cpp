#include "downloader.h"
#include "installer.h"
#include <iostream>
#include <memory>
#include <wx/zipstrm.h>

ProgressDlg::ProgressDlg(wxWindow* parent)
    : wxProgressDialog("Processing...", "Downloading the original installer", 100, parent,
                       wxPD_APP_MODAL | wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_CAN_ABORT)
{
    request = wxWebSession::GetDefault().CreateRequest(this, PKG_LINK);

    Bind(wxEVT_WEBREQUEST_STATE, [this](wxWebRequestEvent& evt)
    {
        switch (evt.GetState())
        {
            case wxWebRequest::State_Completed:
            {
                Update(0, "Unpacking...");
                std::unique_ptr<wxZipEntry> entry;
                wxZipInputStream zip(*evt.GetResponse().GetStream());

                while (entry.reset(zip.GetNextEntry()), entry.get() != nullptr)
                {
                    wxString name = entry->GetName();
                    std::cout << name << std::endl;
                }
                break;
            }

            case wxWebRequest::State_Failed:
                wxLogError("Unable to fetch!\n%s", evt.GetErrorDescription());
                break;
            
            // TODO
            default: break;
        }
    });
    request.Start();
}