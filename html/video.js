var video;

function init() {                                                                              
  if (urltext.indexOf('?') != -1)                                                                 
        targeturl = urltext.substring((urltext.indexOf('?')+1),urltext.length);                 
  else                                                                                            
        targeturl = document.location.href; // defaults to current page if noparameter is passed
                                                                                              
document.getElementById("video").src = targeturl;                                             
                                                                                              
}
function setValue() {
	video = document.getElementById('video');
	playVid();
}

function checkStatus() {
	console.log("checkStatus");
	video.addEventListener('canplay',playVid,true);
}

function playVid() {
// Create variables for all relevant elements
//	var video = document.getElementById('video');
	var pause =  document.getElementById('pause');
	var play =  document.getElementById('play');
	var seekb =  document.getElementById('seekb');
	var seekf =  document.getElementById('seekf');
	var scale =  document.getElementById('scale');
	var ffw =  document.getElementById('ffw');
	var rew =  document.getElementById('rew');
	var timer = document.getElementById('timer');
	var duration = document.getElementById('duration');
	var volume = document.getElementById('volume');
	var vUp = document.getElementById('v-up');
	var vDn = document.getElementById('v-dn');
	var fullSize = true;
	var origWidth = 0;
	var origHeight = 0;
	var t; // This is for the timer
    var animTimer;
    var animStart;

// Set some initial values in the page
	volume.firstChild.nodeValue = Math.round(video.volume*10);
	duration.firstChild.nodeValue = Math.round(video.duration);
// Function to begin the timer
	function startCount() {
		console.log("startCount");
		t = window.setInterval(function() {
			console.log("interval");
			if (video.ended != true) {
				timer.firstChild.nodeValue = Math.round(video.currentTime + 1);
			} else {
				play.firstChild.nodeValue = 'Play';
				window.clearInterval(t);
			}
		},1000);
	}
// Function to pause the timer
	function pauseCount() {
		window.clearInterval(t);
	}
// Play & pause when the control is clicked
	play.addEventListener('click',playControl,false);
	video.addEventListener('click',playControl,false);
	function playControl() {
		if (video.paused == false && video.playbackRate == 1) {
			video.pause();
			this.firstChild.nodeValue = 'Play';
			pauseCount();
		} else {
			if (video.playbackRate == 1) {
				video.play();
			} else {
				video.playbackRate = 1;
			}
			this.firstChild.nodeValue = 'Pause';
			duration.firstChild.nodeValue = Math.round(video.duration);
			startCount();
		}
	}
// Seek backwards and forwards when one of the buttons is clicked
	seekb.addEventListener('click',seekBackwards,false);
	seekf.addEventListener('click',seekForwards,false);
	function seekBackwards() {
		video.currentTime -= 15;
	}
	function seekForwards() {
		video.currentTime += 15;
	}

// Fast forward / rewind
	ffw.addEventListener('click',fastForward,false);
	rew.addEventListener('click',rewind,false);
	function fastForward() {
		play.firstChild.nodeValue = 'Play';
		video.playbackRate = 15;
	}
	function rewind() {
		play.firstChild.nodeValue = 'Play';
		video.playbackRate = -15;
	}

// Scale video
	scale.addEventListener('click',scaleVideo,false);
	function scaleVideo() {
		if (fullSize) {
			origWidth = video.width;
			origHeight = video.height;
		}
		fullSize = !fullSize;

        animStart = new Date().getTime();
        animTimer = setInterval(function(){animFrame()}, 30);
	}

    function animFrame() {
        elapsed = new Date().getTime() - animStart;
        completed = elapsed / 500;
        if(completed < 1) {
            if(fullSize) {
                width = animInterpolate(origWidth/2, origWidth, completed);
                height = animInterpolate(origHeight/2, origHeight, completed);
            }
            else {
                width = animInterpolate(origWidth, origWidth/2, completed);
                height = animInterpolate(origHeight, origHeight/2, completed);
            }
        }
        else {
            clearInterval(animTimer);
            if(fullSize) {
                width = origWidth;
                height = origHeight;
            }
            else {
                width = origWidth/2;
                height = origHeight/2;
            }
        }
        video.width = width;
        video.height = height;
    }
    function animInterpolate(start, end, completed) {
	    if(completed < 0)
		    return start;
	    if(completed > 1)
		    return end;
	    return start + ((end-start)*completed);
    }


// Increase the volume
	vUp.addEventListener('click',volUp,false);
	function volUp() {
		if (video.volume < 1) {
			video.volume = Math.round((video.volume + 0.1)*10)/10;
			volume.firstChild.nodeValue = Math.round(video.volume*10);
		}
	}
// Decrease the volume
	vDn.addEventListener('click',volDown,false);
	function volDown() {
		if (video.volume > 0) {
			video.volume = Math.round((video.volume - 0.1)*10)/10;
			volume.firstChild.nodeValue = Math.round(video.volume*10);
		}
	}

	// Vadim:
	if (video.paused == false) {
		play.firstChild.nodeValue = 'Pause';
		startCount();
	} else {
		play.firstChild.nodeValue = 'Play';
		pauseCount();
	}
}

window.onload = setValue;
