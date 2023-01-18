import '../App.css';
export default function Rectangle({pri}){
    // console.log(pri)
    console.log(`transform: rotate3d(${pri.pitch}, ${pri.roll}, ${pri.yaw},3.14rad)`)
    return (
        <div className="scene">
            <div className="cube"
                 // style={{transform: `rotate3d(${pri.pitch}, ${pri.roll}, ${pri.yaw},3.14rad)`
                 style={{transform: `translateZ(-100px) rotateZ(${pri.pitch}rad) rotateX(${-pri.roll}rad) rotateY(${pri.yaw}rad)`
            }}>
                <div className="cube__face cube__face--front">front</div>
                <div className="cube__face cube__face--back">back</div>
                <div className="cube__face cube__face--right">right</div>
                <div className="cube__face cube__face--left">left</div>
                <div className="cube__face cube__face--top">top</div>
                <div className="cube__face cube__face--bottom">bottom</div>
            </div>
        </div>

        // <div className='rectangle'
        //     style={{transform: `rotate3d(${pri.pitch}, ${pri.roll}, ${pri.yaw},3.14rad)`}}
        // />
    )
}