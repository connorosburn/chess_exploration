import React, {useState, useEffect} from 'react';
import ActiveGame from './ActiveGame';
import NewGame from './NewGame';
import AppHeader from './AppHeader'
import MenuBar from './MenuBar';
import Registration from './Users/Registration.jsx';
import Login from './Users/Login.jsx';
import OnlineGames from './OnlineGames';
import LiveGameListener from './request/socket.js';
import {checkLogin, logout, getGame, startGame} from './request/fetch'

function UserInterface(props) {
    const[displayMode, setDisplayMode] = useState('new-game');
    const[userInfo, setUserInfo] = useState(null);
    const[loginChecked, setLoginChecked] = useState(false);
    const[activeGameConfig, setActiveGameConfig] = useState(null);
    const[resetGame, setResetGame] = useState(false);
    const [gameType, setGameType] = useState('chess');

    useEffect(() => {
        const loginCheck = async () => {
            let userInfo = await checkLogin();
            if(Object.keys(userInfo).length > 0) {
                setUserInfo(userInfo);
            }
            setLoginChecked(true);
        }
        loginCheck();
    }, []);

    const setUpGame = async (config) => {
        if(config.hasOwnProperty('gameID')) {
            let response = await getGame(config.gameID);
            let data = await response.json();
            config.snapshot = data.snapshot;
        }
        setActiveGameConfig(config);
        setResetGame(true);
        setDisplayMode('active-game');
    }

    const displayBody = () => {
        switch(displayMode) {
            case 'online-games':
                return (
                    <OnlineGames 
                        setUpGame={setUpGame}
                    />
                );
            case 'registration':
                return (
                    <Registration
                        resetPage={() => setDisplayMode('new-game')}
                        setUserInfo={setUserInfo}
                    />
                );
            case 'login':
                return (
                    <Login
                        resetPage={() => setDisplayMode('new-game')}
                        setUserInfo={setUserInfo}
                    />
                );
            case 'new-game':
                return (
                    <NewGame
                        loggedIn={userInfo != null}
                        setUpGame={setUpGame}
                        loginChecked = {loginChecked}
                    />
                );
            case 'active-game':
                return (
                    <ActiveGame
                        config={activeGameConfig}
                        resetGame={() => {
                            const reset = resetGame;
                            setResetGame(false);
                            return reset;
                        }}
                        startGame={async (move) => {
                            let response = await startGame(move, activeGameConfig.opponent);
                            if(response.status == 200) {
                                let newConfig = activeGameConfig;
                                let data = await response.json();
                                newConfig.gameID = data.id;
                                newConfig.listener = new LiveGameListener(data.id);
                                setActiveGameConfig(newConfig);
                            } else {
                                setDisplayMode('new-game')
                                setActiveGameConfig(null);
                            }
                        }}
                        gameType={gameType}
                    />
                );
            default:
                return <div></div>
        }
    }
    return (
        <div className="app-wrapper">
            <AppHeader
                loginChecked = {loginChecked}
                selected={displayMode}
                setDisplayMode={setDisplayMode}
                userInfo={userInfo}
                logout={async () => {
                        setUserInfo(null)
                        setActiveGameConfig(null)
                        await logout();
                    }
                }
            />
            <MenuBar 
                selected={displayMode} 
                gameActive={activeGameConfig != null}
                setDisplayMode={setDisplayMode}
                loggedIn={userInfo != null}
            />
            <div className="app-body">
                {displayBody()}
            </div>
        </div>
    );
}

export default UserInterface;