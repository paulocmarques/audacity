/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "ui/iuiactionsmodule.h"
#include "trackeditactionscontroller.h"
#include "modularity/ioc.h"
#include "context/iuicontextresolver.h"
#include "async/asyncable.h"
#include "playback/iaudiodevicesprovider.h"

namespace au::trackedit {
class TrackeditUiActions : public muse::ui::IUiActionsModule, public muse::async::Asyncable
{
    muse::Inject<context::IUiContextResolver> uicontextResolver;
    muse::Inject<playback::IAudioDevicesProvider> audioDevicesProvider;

public:
    TrackeditUiActions(std::shared_ptr<TrackeditActionsController> controller);

    void init();

    const muse::ui::UiActionList& actionsList() const override;

    bool actionEnabled(const muse::ui::UiAction& act) const override;
    muse::async::Channel<muse::actions::ActionCodeList> actionEnabledChanged() const override;

    bool actionChecked(const muse::ui::UiAction& act) const override;
    muse::async::Channel<muse::actions::ActionCodeList> actionCheckedChanged() const override;

private:
    muse::ui::UiActionList m_actions;

    std::shared_ptr<TrackeditActionsController> m_controller;
    muse::async::Channel<muse::actions::ActionCodeList> m_actionEnabledChanged;
    muse::async::Channel<muse::actions::ActionCodeList> m_actionCheckedChanged;
};
}
