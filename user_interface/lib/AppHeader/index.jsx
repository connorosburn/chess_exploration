import React from 'react';
import LoginButtons from './LoginButtons.jsx';

function AppHeader(props) {
    const labelText = () => {
        let label = ' ';
        if(props.gameType == 'chess') {
            label = `The ${props.gameType}`
        } else {
            label = `The stuff: ${props.gameType.replace(/-/g, ' ')}`
        }
        return label;
    }

    return (
        <div className="app-header">
            <div className="left-margin"></div>
            <div className="title">
                <h1>Chess N' Stuff</h1>
                <p className="game-label-text">
                    {labelText()}
                </p>
            </div>
            <LoginButtons
                selected={props.selected} 
                setDisplayMode={props.setDisplayMode}
                logout={props.logout}
                userInfo={props.userInfo}
                loginChecked={props.loginChecked}
            />
        </div>
    );
}

export default AppHeader;