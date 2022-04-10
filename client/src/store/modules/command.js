let socket = WebSocket.prototype // 
const getDefaultState = () => {
    return {
        data: {},
        sending: false,

        responseTime: -1,
        lastPongTime: -1,

        uptime: 0
    }
}
const command = {
    state: getDefaultState(),
    mutations: {
        resetState(state) {
            // Merge rather than replace so we don't lose observers
            // https://github.com/vuejs/vuex/issues/1118
            Object.assign(state, getDefaultState())
        },
        setData: function (state, data) {
            try {
                let objData = JSON.parse(data)
                if (objData.cmd == "pong") {
                    state.uptime = objData.stamp
                    state.lastPongTime = Date.now()
                }
            } catch (error) {
                let tmp = {}
                let lines = data.split('\n')
                lines.forEach(line => {
                    let elm = line.split(':')
                    tmp[elm[0]] = elm[1]
                });
                state.data = { ...state.data, ...tmp }
            }
           

        },
        setSending: function (state, status) {
            state.sending = status
        },
        updateResponseTime: function (state) {
            state.responseTime = 1000 - (Date.now() - state.lastPongTime)
        },
    },
    actions: {
        initCommand: function (context) {
            // socket = new WebSocket('ws://' + "192.168.2.101" + ':81/')

            socket = new WebSocket('ws://' + window.location.hostname + ':81/');

            socket.addEventListener('message', function (event) {
                context.commit("setData", event.data)
                context.commit("setSending", false)
            });
            socket.addEventListener('open', function () {
                let obj = {
                    cmd: "gal"
                }
                socket.send(JSON.stringify(obj))
                setInterval(() => {
                    context.commit("updateResponseTime")
                    let obj = {
                        cmd: "ping"
                    }
                    if (socket.readyState == WebSocket.OPEN)
                        socket.send(JSON.stringify(obj))
                }, 1000)
            });
        },
        closeWebsocket: function (context) {
            socket.close()
            context.commit("resetState")
        },
        sendCommand: function (context, { espKey, espValue }) {
            if (espValue != undefined)
                espValue = espValue.toString()
            else
                espValue = ""
            let obj = {
                cmd: "exe",
                key: espKey,
                val: espValue
            }
            if (socket.readyState == WebSocket.OPEN){
                socket.send(JSON.stringify(obj))
            }
            context.commit("setSending", true)
        },


    },
    getters: {
        getData: function (state) {
            return state.data
        },
        getSending: function (state) {
            return state.sending
        },
        getResponseTime: function (state) {
            return state.responseTime
        },
        getUptime: function (state) {
            return Math.floor(state.uptime / 1000)
        },
    }
}
export default command
