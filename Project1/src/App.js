import React from 'react';
import logo from './logo.svg';
import Peer from 'peerjs';

import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
         P2P
        </p>
      </header>
    </div>
  );
}

 function getInitialState(){
  return {
    peer: new Peer({
      host: 'localhost', port: 3000, path: '/peerjs',
      debug: 3,
      config: {'iceServers': [
        { url: 'stun:stun1.l.google.com:19302' },
        { url: 'turn:numb.viagenie.ca', credential: 'muazkh', username: 'webrtc@live.com' }
      ]}
    }),
    my_id: '',
    peer_id: '',
    initialized: false,
    files: []
  }
}

export default App;
