import './App.css';
import Rectangle from "./components/Rectangle";
import {useEffect, useState} from "react";

function App() {
    const [ip, setIp] = useState("")
    const [pri, setPri] = useState({})
    useEffect(() => {
        var gateway = `ws://192.168.1.169/ws`;
        var websocket;

        function initWebSocket() {
            console.log('Trying to open a WebSocket connection...');
            websocket = new WebSocket(gateway);
            websocket.onopen = onOpen;
            websocket.onclose = onClose;
            websocket.onmessage = onMessage; // <-- add this line
        }

        function onOpen(event) {
            console.log('Connection opened');
        }

        function onClose(event) {
            console.log('Connection closed');
            setTimeout(initWebSocket, 2000);
        }

        function onMessage(event) {
            const data = JSON.parse(event.data)
            console.log(data)
            if (data?.imuData) {
                setPri(data.imuData)
            }

            if (data?.IP){
                setIp(data.IP)
            }
            // console.log(imuData)
        }

        window.addEventListener('load', onLoad);

        function onLoad(event) {
            initWebSocket();
            initButton();
        }

        onLoad()

        function initButton() {
            // document.getElementById('button').addEventListener('click', toggle);
        }

        function toggle() {
            websocket.send('toggle');
        }
    }, [])


    return (
        <div className="App">
            {
                ip.length>0?
                Object.keys(pri).length > 0 ?
                    <Rectangle pri={pri} ip={ip}/>
                    : "Don't have pri ..."
                    : "Ip doesn't set ..."
            }
        </div>
    );
}

export default App;
