document.addEventListener('DOMContentLoaded', main);

function main() {
    setInterval(function() {
        const req = new XMLHttpRequest()
        req.open("GET", "/buttons")
        req.send()
        req.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
                let resp = this.responseText.split("/")
                document.querySelector("#buttons").innerHTML = `left = ${resp[0]} 
                mid = ${resp[1]} right = ${resp[2]}`
            }
        }
    }, 1000)

    document.querySelector("#motor_on").onclick = function() {
        const req = new XMLHttpRequest()
        //const params = 
        req.open("GET", "/motor_on?par1=a&par2=b&par3=c")
        req.send()
        console.log("motor_on")
    }

    document.querySelector("#motor_off").onclick = function() {
        const req = new XMLHttpRequest()
        //const params = 
        req.open("GET", "/motor_off?par1=a&par2=b&par3=c")
        req.send()
        console.log("motor_off")
    }

    document.querySelector("#led").onclick = function() {
        const req = new XMLHttpRequest()
        req.open("GET", "/led")
        req.send()
        console.log("on")
    }

}