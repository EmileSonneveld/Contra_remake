/* (c) 2008-2012 Add This, LLC */
if(!window._ate)
{ 
	(function()
	{ 
		var l; 
		try
		{ 
			l=window.location; 
			if(l.protocol.indexOf("file")===0||l.protocol.indexOf("safari-extension")===0||l.protocol.indexOf("chrome-extension")===0)
			{ 
				_atr="http:"+_atr; 
			} 
			if(l.hostname.indexOf("localhost")!=-1)
			{ 
				_atc.loc=1; 
			} 
		} 
		catch(e)
		{ 
		} 
		var ua=navigator.userAgent.toLowerCase(),d=document,w=window,dl=d.location,b=
		{ 
win:/windows/.test(ua),xp:(/windows nt 5.1/.test(ua))||(/windows nt 5.2/.test(ua)),osx:/os x/.test(ua),chr:/chrome/.test(ua),chb:/chrome\/(1[456789])/.test(ua),iph:/iphone/.test(ua),dro:/android/.test(ua),ipa:/ipad/.test(ua),saf:/safari/.test(ua)&&!(/chrome/.test(ua)),opr:/opera/.test(ua),msi:(/msie/.test(ua))&&!(/opera/.test(ua)),ffx:/firefox/.test(ua),ff2:/firefox\/2/.test(ua),ffn:/firefox\/((3.[6789][0-9a-z]*)|(4.[0-9a-z]*))/.test(ua),ie6:/msie 6.0/.test(ua),ie7:/msie 7.0/.test(ua),ie8:/msie 8.0/.test(ua),ie9:/msie 9.0/.test(ua),mod:-1} 
			,_7=
			{ 
rev:"110436",bro:b,wlp:(l||
	{ 
	} 
	).protocol,dl:dl,upm:!!w.postMessage&&(""+w.postMessage).toLowerCase().indexOf("[native code]")!==-1,bamp:_atc.bamp-Math.random(),camp:_atc.camp-Math.random(),xamp:_atc.xamp-Math.random(),vamp:_atc.vamp-Math.random(),tamp:_atc.tamp-Math.random(),pamp:_atc.pamp-Math.random(),ab:"-",inst:1,wait:500,tmo:null,sub:!!window.at_sub,dbm:0,uid:null,api:
	{ 
	} 
	,imgz:[],hash:window.location.hash} 
			; 
			d.ce=d.createElement; 
			d.gn=d.getElementsByTagName; 
			window._ate=_7; 
			_7.evl=function(_8,_9)
			{ 
				if(_9)
				{ 
					var _a; 
					eval("evl = "+_8); 
					return _a; 
				} 
				else
				{ 
					return eval(_8); 
				} 
			} 
			; 
			function reduce(o,fn,_d,_e)
			{ 
				if(!o)
				{ 
					return _d; 
				} 
				if(o instanceof Array||(o.length&&(typeof o!=="function")))
				{ 
					for(var i=0,len=o.length,v=o[0]; 
						i<len; 
						v=o[++i])
					{ 
						_d=fn.call(_e||o,_d,v,i,o); 
					} 
				} 
				else
				{ 
					for(var _12 in o)
					{ 
						_d=fn.call(_e||o,_d,o[_12],_12,o); 
					} 
				} 
				return _d; 
			} 
			var _13=function(_14,_15)
			{ 
				reduce(_14,function(acc,v,k)
				{ 
					_15(k,v); 
				} 
				,[]); 
			} 
			,_19=function(a,b)
			{ 
				var _1c=
				{ 
				} 
				,i; 
				for(i=0; 
					i<a.length; 
					i++)
				{ 
					_1c[a[i]]=1; 
				} 
				for(i=0; 
					i<b.length; 
					i++)
				{ 
					if(!_1c[b[i]])
					{ 
						a.push(b[i]); 
						_1c[b[i]]=1; 
					} 
				} 
				return a; 
			} 
			,_1e=Array.prototype.slice,_1f=function(a)
			{ 
				return _1e.apply(a,_1e.call(arguments,1)); 
			} 
			,_21=function(s)
			{ 
				return(""+s).replace(/(^\s+|\s+$)/g,""); 
			} 
			,_23=function(A,B)
			{ 
				return reduce(_1f(arguments,1),function(A,_27)
				{ 
					return reduce(_27,function(o,v,k)
					{ 
						if(o)
						{ 
							o[k]=v; 
						} 
						return o; 
					} 
					,A); 
				} 
				,A); 
			} 
			,_2b=function(o,del)
			{ 
				return reduce(o,function(acc,v,k)
				{ 
					k=_21(k); 
					if(k)
					{ 
						acc.push(_euc(k)+"="+_euc(_21((typeof(v)=="object"?_2b(v,(del||"&")):(v))))); 
					} 
					return acc; 
				} 
				,[]).join(del||"&"); 
			} 
			,_31=function(o,del)
			{ 
				return reduce(o,function(acc,v,k)
				{ 
					k=_21(k); 
					if(k)
					{ 
						acc.push(_euc(k)+"="+_euc(_21(v))); 
					} 
					return acc; 
				} 
				,[]).join(del||"&"); 
			} 
			,_37=function(q,del)
			{ 
				return reduce((q||"").split(del||"&"),function(acc,_3b)
				{ 
					try
					{ 
						var kv=_3b.split("="),k=_21(_duc(kv[0])),v=_21(_duc(kv.slice(1).join("="))); 
						if(v.indexOf(del||"&")>-1||v.indexOf("=")>-1)
						{ 
							v=_37(v,del||"&"); 
						} 
						if(k)
						{ 
							acc[k]=v; 
						} 
					} 
					catch(e)
					{ 
					} 
					return acc; 
				} 
				,
				{ 
				} 
				); 
			} 
			,_3f=function(q,del)
			{ 
				return reduce((q||"").split(del||"&"),function(acc,_43)
				{ 
					try
					{ 
						var kv=_43.split("="),k=_21(_duc(kv[0])),v=_21(_duc(kv.slice(1).join("="))); 
						if(k)
						{ 
							acc[k]=v; 
						} 
					} 
					catch(e)
					{ 
					} 
					return acc; 
				} 
				,
				{ 
				} 
				); 
			} 
			,_47=function(obj)
			{ 
				if(null==obj||"object"!=typeof obj)
				{ 
					return obj; 
				} 
				if(obj instanceof Object)
				{ 
					var s=""; 
					for(var _4a in obj)
					{ 
						if(obj.hasOwnProperty(_4a))
						{ 
							s+=((s.length>0)?",":"")+obj[_4a]; 
						} 
					} 
					return s; 
				} 
				return null; 
			} 
			,_4b=function()
			{ 
				var _4c=_1f(arguments,0),fn=_4c.shift(),_4e=_4c.shift(); 
				return function()
				{ 
					return fn.apply(_4e,_4c.concat(_1f(arguments,0))); 
				} 
				; 
			} 
			,_4f=function(un,obj,evt,fn)
			{ 
				if(!obj)
				{ 
					return; 
				} 
				if(we)
				{ 
					obj[(un?"detach":"attach")+"Event"]("on"+evt,fn); 
				} 
				else
				{ 
					obj[(un?"remove":"add")+"EventListener"](evt,fn,false); 
				} 
			} 
			,_54=function(obj,evt,fn)
			{ 
				_4f(0,obj,evt,fn); 
			} 
			,_58=function(obj,evt,fn)
			{ 
				_4f(1,obj,evt,fn); 
			} 
			,_5c=function(s)
			{ 
				return(s.match(/(([^\/\/]*)\/\/|\/\/)?([^\/\?\&\#]+)/i))[0]; 
			} 
			,_5e=function(s)
			{ 
				return s.replace(_5c(s),""); 
			} 
			,_60=function(obj)
			{ 
				if(null==obj||"object"!=typeof obj)
				{ 
					return obj; 
				} 
				if(obj instanceof Object)
				{ 
					var _62=
					{ 
					} 
					; 
					for(var _63 in obj)
					{ 
						if(obj.hasOwnProperty(_63))
						{ 
							_62[_63]=_60(obj[_63]); 
						} 
					} 
					return _62; 
				} 
				return null; 
			} 
			,_64=
			{ 
unqconcat:_19,reduce:reduce,slice:_1f,strip:_21,extend:_23,toKV:_31,rtoKV:_2b,fromKV:_3f,rfromKV:_37,otoCSV:_47,bind:_4b,listen:_54,unlisten:_58,gUD:_5c,gUQS:_5e,clone:_60} 
				; 
				_7.util=_64; 
				_23(_7,_64); 
				(function(i,k,l)
				{ 
					var g,n=i.util; 
					function j(q,p,s,o,r)
					{ 
						this.type=q; 
						this.triggerType=p||q; 
						this.target=s||o; 
						this.triggerTarget=o||s; 
						this.data=r||
						{ 
						} 
						; 
					} 
					n.extend(j.prototype,
					{ 
constructor:j,bubbles:false,preventDefault:n.noop,stopPropagation:n.noop,clone:function()
			{ 
				return new this.constructor(this.type,this.triggerType,this.target,this.triggerTarget,n.extend(
				{ 
				} 
				,this.data)); 
			} 
					} 
					); 
					function e(o,p)
					{ 
						this.target=o; 
						this.queues=
						{ 
						} 
						; 
						this.defaultEventType=p||j; 
					} 
					function a(o)
					{ 
						var p=this.queues; 
						if(!p[o])
						{ 
							p[o]=[]; 
						} 
						return p[o]; 
					} 
					function h(o,p)
					{ 
						this.getQueue(o).push(p); 
					} 
					function d(p,r)
					{ 
						var s=this.getQueue(p),o=s.indexOf(r); 
						if(o!==-1)
						{ 
							s.splice(o,1); 
						} 
					} 
					function b(o,s,r,q)
					{ 
						var p=this; 
						if(!q)
						{ 
							setTimeout(function()
							{ 
								p.dispatchEvent(new p.defaultEventType(o,o,s,p.target,r)); 
							} 
							,10); 
						} 
						else
						{ 
							p.dispatchEvent(new p.defaultEventType(o,o,s,p.target,r)); 
						} 
					} 
					function m(p)
					{ 
						for(var r=0,t=p.target,s=this.getQueue(p.type),o=s.length; r<o; r++)
						{ 
							s[r].call(t,p.clone()); 
						} 
					} 
					function c(p)
					{ 
						if(!p)
						{ 
							return; 
						} 
						for(var o in f)
						{ 
							p[o]=n.bind(f[o],this); 
						} 
						return p; 
					} 
					var f=
					{ 
constructor:e,getQueue:a,addEventListener:h,removeEventListener:d,dispatchEvent:m,fire:b,decorate:c} 
						; 
						n.extend(e.prototype,f); 
						i.event=
						{ 
PolyEvent:j,EventDispatcher:e} 
							; 
				} 
				)(_7,_7.api,_7); 
				_7.ed=new _7.event.EventDispatcher(_7); 
				var _87=
				{ 
isBound:0,isReady:0,readyList:[],onReady:function()
		{ 
			if(!_87.isReady)
			{ 
				_87.isReady=1; 
				var l=_87.readyList.concat(window.addthis_onload||[]); 
				for(var fn=0; 
					fn<l.length; 
					fn++)
				{ 
					l[fn].call(window); 
				} 
				_87.readyList=[]; 
			} 
		} 
		,addLoad:function(_8a)
		{ 
			var o=w.onload; 
			if(typeof w.onload!="function")
			{ 
				w.onload=_8a; 
			} 
			else
			{ 
				w.onload=function()
				{ 
					if(o)
					{ 
						o(); 
					} 
					_8a(); 
				} 
				; 
			} 
		} 
		,bindReady:function()
		{ 
			if(r.isBound||_atc.xol)
			{ 
				return; 
			} 
			r.isBound=1; 
			if(document.readyState==="complete")
			{ 
				return setTimeout(r.onReady,1); 
			} 
			if(d.addEventListener&&!b.opr)
			{ 
				d.addEventListener("DOMContentLoaded",r.onReady,false); 
			} 
			var apc=window.addthis_product; 
			if(apc&&apc.indexOf("f")>-1)
			{ 
				r.onReady(); 
				return; 
			} 
			if(b.msi&&!b.ie9&&window==top)
			{ 
				(function()
				{ 
					if(r.isReady)
					{ 
						return; 
					} 
					try
					{ 
						d.documentElement.doScroll("left"); 
					} 
					catch(error)
					{ 
						setTimeout(arguments.callee,0); 
						return; 
					} 
					r.onReady(); 
				} 
				)(); 
			} 
			if(b.opr)
			{ 
				d.addEventListener("DOMContentLoaded",function()
				{ 
					if(r.isReady)
					{ 
						return; 
					} 
					for(var i=0; 
						i<d.styleSheets.length; 
						i++)
					{ 
						if(d.styleSheets[i].disabled)
						{ 
							setTimeout(arguments.callee,0); 
							return; 
						} 
					} 
					r.onReady(); 
				} 
				,false); 
			} 
			if(b.saf)
			{ 
				var _8e; 
				(function()
				{ 
					if(r.isReady)
					{ 
						return; 
					} 
					if(d.readyState!="loaded"&&d.readyState!="complete")
					{ 
						setTimeout(arguments.callee,0); 
						return; 
					} 
					if(_8e===undefined)
					{ 
						var _90=d.gn("link"); 
						for(var i=0; 
							i<_90.length; 
							i++)
						{ 
							if(_90[i].getAttribute("rel")=="stylesheet")
							{ 
								_8e++; 
							} 
						} 
						var _92=d.gn("style"); 
						_8e+=_92.length; 
					} 
					if(d.styleSheets.length!=_8e)
					{ 
						setTimeout(arguments.callee,0); 
						return; 
					} 
					r.onReady(); 
				} 
				)(); 
			} 
			r.addLoad(r.onReady); 
		} 
		,append:function(fn,_94)
		{ 
			r.bindReady(); 
			if(r.isReady)
			{ 
				fn.call(window,[]); 
			} 
			else
			{ 
				r.readyList.push(function()
				{ 
					return fn.call(window,[]); 
				} 
				); 
			} 
		} 
				} 
				,r=_87,a=_7; 
				_23(_7,
				{ 
plo:[],lad:function(x)
	{ 
		_7.plo.push(x); 
	} 
				} 
				); 
				(function(c,e,d)
				{ 
					var a=window; 
					c.pub=function()
					{ 
						return _euc((window.addthis_config||
						{ 
						} 
						).pubid||(window.addthis_config||
						{ 
						} 
						).username||window.addthis_pub||""); 
					} 
					; 
					c.usu=function(g,h)
					{ 
						if(!a.addthis_share)
						{ 
							a.addthis_share=
							{ 
							} 
							; 
						} 
						if(h||g!=addthis_share.url)
						{ 
							addthis_share.imp_url=0; 
						} 
					} 
					; 
					c.rsu=function()
					{ 
						var h=document,g=h.title,f=h.location?h.location.href:""; 
						if(_atc.ver>=250&&addthis_share.imp_url&&f&&f!=a.addthis_share.url&&!(_7.util.ivc((h.location.hash||"").substr(1).split(",").shift())))
						{ 
							a.addthis_share.url=a.addthis_url=f; 
							a.addthis_share.title=a.addthis_title=g; 
							return 1; 
						} 
						return 0; 
					} 
					; 
					c.igv=function(f,g)
					{ 
						if(!a.addthis_config)
						{ 
							a.addthis_config=
							{ 
username:a.addthis_pub} 
								; 
						} 
						else
						{ 
							if(addthis_config.data_use_cookies===false)
							{ 
								_atc.xck=1; 
							} 
						} 
						if(!a.addthis_share)
						{ 
							a.addthis_share=
							{ 
							} 
							; 
						} 
						if(!addthis_share.url)
						{ 
							if(!a.addthis_url&&addthis_share.imp_url===undefined)
							{ 
								addthis_share.imp_url=1; 
							} 
							addthis_share.url=(a.addthis_url||f||"").split("#
							{ 
								").shift(); 
							} 
							if(!addthis_share.title)
							{ 
								addthis_share.title=(a.addthis_title||g||"").split("#
								{ 
									").shift(); 
								} 
							} 
							; 
							if(!_atc.ost)
							{ 
								if(!a.addthis_conf)
								{ 
									a.addthis_conf=
									{ 
									} 
									; 
								} 
								for(var b in addthis_conf)
								{ 
									_atc[b]=addthis_conf[b]; 
								} 
								_atc.ost=1; 
							} 
						} 
						)(_7,_7.api,_7); 
						(function(b,f,c)
						{ 
							var h,g=document,a=b.util; 
							b.ckv=a.fromKV(g.cookie,"; 
								"); 
								function e(d)
							{ 
								return a.fromKV(g.cookie,"; 
									")[d]; 
							} 
							if(!b.cookie)
							{ 
								b.cookie=
								{ 
								} 
								; 
							} 
							b.cookie.rck=e; 
						} 
						)(_7,_7.api,_7); 
						(function(b,c,e)
						{ 
							var a,h=document,g=0; 
							function j()
							{ 
								if(g)
								{ 
									return 1; 
								} 
								k("xtc",1); 
								if(1==b.cookie.rck("xtc"))
								{ 
									g=1; 
								} 
								f("xtc",1); 
								return g; 
							} 
							function l(n)
							{ 
								if(_atc.xck)
								{ 
									return; 
								} 
								var m=n||_7.dh||_7.du||(_7.dl?_7.dl.hostname:""); 
								if(m.indexOf(".gov")>-1||m.indexOf(".mil")>-1)
								{ 
									_atc.xck=1; 
								} 
								var o=typeof(b.pub)==="function"?b.pub():b.pub,d=["usarmymedia","govdelivery"]; 
								for(i in d)
								{ 
									if(o==d[i])
									{ 
										_atc.xck=1; 
										break; 
									} 
								} 
							} 
							function f(m,d)
							{ 
								if(h.cookie)
								{ 
									h.cookie=m+"=; 
										expires=Thu, 01 Jan 1970 00:00:01 GMT; 
									path=/"+(d?"; 
									domain="+(b.bro.msi?"":".")+"addthis.com":""); 
								} 
							} 
							function k(n,m,o,p,d)
							{ 
								if(!window.at_sub)
								{ 
									l(); 
								} 
								if(!_atc.xck)
								{ 
									if(!d)
									{ 
										var d=new Date(); 
										d.setYear(d.getFullYear()+2); 
									} 
									document.cookie=n+"="+m+(!o?"; 
										expires="+d.toUTCString():"")+"; 
									path=/; 
									"+(!p?" domain="+(b.bro.msi?"":".")+"addthis.com":""); 
								} 
							} 
							if(!b.cookie)
							{ 
								b.cookie=
								{ 
								} 
								; 
							} 
							b.cookie.sck=k; 
							b.cookie.kck=f; 
							b.cookie.cww=j; 
							b.cookie.gov=l; 
						} 
						)(_7,_7.api,_7); 
						(function(d,g,e)
						{ 
							var c=d.util,a=
							{ 
							} 
							,b=
							{ 
							} 
							; 
							if(!d.cbs)
							{ 
								d.cbs=
								{ 
								} 
								; 
							} 
							function f(k,j,n,l,h)
							{ 
								j=(_euc(j)).replace(/[0-3][A-Z]|[^a-zA-Z0-9]/g,""); 
								a[j]=a[j]||0; 
								var i=a[j]++,m=k+"_"+j+(!h?i:""); 
								if(!_7.cbs[m])
								{ 
									_7.cbs[m]=function()
									{ 
										if(b[m])
										{ 
											clearTimeout(b[m]); 
										} 
										n.apply(this,arguments); 
									} 
									; 
								} 
								_7.cbs["time_"+m]=(new Date()).getTime(); 
								if(l)
								{ 
									clearTimeout(b[m]); 
									b[m]=setTimeout(l,10000); 
								} 
								return"_ate.cbs."+_euc(m); 
							} 
							c.scb=f; 
						} 
						)(_7,_7.api,_7); 
						(function(b,d,c)
						{ 
							function e()
							{ 
								var k=a(navigator.userAgent,16),f=((new Date()).getTimezoneOffset())+""+navigator.javaEnabled()+(navigator.userLanguage||navigator.language),h=window.screen.colorDepth+""+window.screen.width+window.screen.height+window.screen.availWidth+window.screen.availHeight,g=navigator.plugins,l=g.length; 
								if(l>0)
								{ 
									for(var j=0; 
										j<Math.min(10,l); 
										j++)
									{ 
										if(j<5)
										{ 
											f+=g[j].name+g[j].description; 
										} 
										else
										{ 
											h+=g[j].name+g[j].description; 
										} 
									} 
								} 
								return k.substr(0,2)+a(f,16).substr(0,3)+a(h,16).substr(0,3); 
							} 
							function a(h,j)
							{ 
								var f=291; 
								if(h)
								{ 
									for(var g=0; 
										g<h.length; 
										g++)
									{ 
										f=(f*(h.charCodeAt(g)+g)+3)&1048575; 
									} 
								} 
								return(f&16777215).toString(j||32); 
							} 
							b.mun=a; 
							b.gub=e; 
						} 
						)(_7,_7.api,_7); 
						(function(d,e,g)
						{ 
							var c,l=d.util,j=4294967295,b=new Date().getTime(); 
							function h()
							{ 
								return((b/1000)&j).toString(16)+("00000000"+(Math.floor(Math.random()*(j+1))).toString(16)).slice(-8); 
							} 
							function a(m)
							{ 
								return k(m)?(new Date((parseInt(m.substr(0,8),16)*1000))):new Date(); 
							} 
							function i(m)
							{ 
								var n=a(); 
								return((n.getTime()-1000*86400)>(new Date()).getTime()); 
							} 
							function f(m,o)
							{ 
								var n=a(m); 
								return(((new Date()).getTime()-n.getTime())>o*1000); 
							} 
							function k(m)
							{ 
								return m&&m.match(/^[0-9a-f]
								{ 
									16} 
								$/)&&!i(m); 
							} 
							l.cuid=h; 
							l.ivc=k; 
							l.ioc=f; 
						} 
						)(_7,_7.api,_7); 
						(function(c,f,e)
						{ 
							function b(g)
							{ 
								if(!g)
								{ 
									return""; 
								} 
								else
								{ 
									if(g.indexOf("%")>-1)
									{ 
										g=_duc(g); 
									} 
								} 
								g=_7.util.atob(g.split(",")[1]); 
								return g; 
							} 
							function d(h)
							{ 
								var j=
								{ 
								} 
								,g,i; 
								j.zip=h.substring(0,5); 
								j.continent=h.substring(5,7); 
								j.country=h.substring(7,9); 
								j.region=h.substring(9,11); 
								g=h.substring(11,15); 
								if(g!="0000")
								{ 
									j.lat=(parseInt(g)/10-180).toFixed(1); 
								} 
								i=h.substring(15,19); 
								if(i!="0000")
								{ 
									j.lon=(parseInt(i)/10-180).toFixed(1); 
								} 
								j.dma=h.substring(19,22); 
								j.msa=h.substring(22,26); 
								j.network_type=h.substring(26,27); 
								j.throughput=h.substring(27,28); 
								return j; 
							} 
							function a(j,k)
							{ 
								var h,g; 
								j=j.split(","); 
								for(h=0; 
									h<j.length; 
									h++)
								{ 
									g=j[h].replace(/ /g,""); 
									if(k.zip==g||k.continent==g||k.country==g||k.region==g)
									{ 
										return 1; 
									} 
								} 
								return 0; 
							} 
							c.util=c.util||
							{ 
							} 
							; 
							c.util.geo=
							{ 
dec:b,parse:d,isin:a} 
								; 
						} 
						)(_7,_7.api,_7); 
						(function(a,c,b)
						{ 
							function d(e)
							{ 
								return e.split("//").pop().split("/").shift().split("#").shift().split("?").shift().split(".").slice(-2).join("."); 
							} 
							a.util=a.util||
							{ 
							} 
							; 
							a.util.host=d; 
						} 
						)(_7,_7.api,_7); 
						(function(c,f,e)
						{ 
							var b=
							{ 
							} 
							; 
							function g(i,h)
							{ 
								var j=i.indexOf("#")>-1&&!h?i.replace(/^[^\#]+\#?|^\#?/,""):i.replace(/^[^\?]+\??|^\??/,""),k=c.util.fromKV(j); 
								return k; 
							} 
							function a(h)
							{ 
								if(b[h])
								{ 
									return b[h]; 
								} 
								else
								{ 
									var k=document.gn("script"); 
									for(var j=0; 
										j<k.length; 
										j++)
									{ 
										b[k[j].src.split(".").slice(-2).shift()]=k[j]; 
										if((k[j].src||"").indexOf(h)>-1)
										{ 
											return k[j]; 
										} 
									} 
								} 
								return null; 
							} 
							function d(m)
							{ 
								var j=document.gn("script"),n=j.length,k=j[n-1],l=g(k.src); 
								if(m||(k.src&&k.src.indexOf("addthis")==-1))
								{ 
									for(var h=0; 
										h<n; 
										h++)
									{ 
										if((j[h].src||"").indexOf(m||"addthis.com")>-1)
										{ 
											b[j[h].src.split(".").slice(-2).shift()]=j[h]; 
											l=g(j[h].src); 
											break; 
										} 
									} 
								} 
								return l; 
							} 
							if(!c.util)
							{ 
								c.util=
								{ 
								} 
								; 
							} 
							c.util.gsp=d; 
							c.util.gst=a; 
							c.util.ghp=g; 
						} 
						)(_7,_7.api,_7); 
						(function(e,g,f)
						{ 
							var d=e.util,b="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_="; 
							function a(k)
							{ 
								var j="",n,l,h,p,o,m=0; 
								if(/[0-9a-fA-F]+/.test(k))
								{ 
									while(m<k.length)
									{ 
										n=parseInt(k.charAt(m++),16); 
										l=parseInt(k.charAt(m++),16); 
										h=parseInt(k.charAt(m++),16); 
										p=(n<<2)|(isNaN(h)?l&3:(l>>2)); 
										o=((l&3)<<4)|h; 
										j+=b.charAt(p)+(isNaN(h)?"":b.charAt(o)); 
									} 
								} 
								return j; 
							} 
							function c(k)
							{ 
								var j="",n,l,h,p,o,m=0; 
								while(m<k.length)
								{ 
									p=b.indexOf(k.charAt(m++)); 
									o=m>=k.length?NaN:b.indexOf(k.charAt(m++)); 
									n=p>>2; 
									l=isNaN(o)?(p&3):(((p&3)<<2)|(o>>4)); 
									h=o&15; 
									j+=n.toString(16)+l.toString(16)+(isNaN(o)?"":h.toString(16)); 
								} 
								return j; 
							} 
							d.hbtoa=a; 
							d.atohb=c; 
						} 
						)(_7,_7.api,_7); 
						(function(f,s,u)
						{ 
							var v=f,j=new Date().getTime(),r=function()
							{ 
								return Math.floor(Math.random()*4294967295).toString(36); 
							} 
							,w=function()
							{ 
								return Math.floor((new Date().getTime()-j)/100).toString(16); 
							} 
							,g=0,i=function(a)
							{ 
								if(g===0)
								{ 
									v.sid=g=(a||v.util.cuid()); 
								} 
								return g; 
							} 
							,d=null,c=function(a,x)
							{ 
								if(d!==null)
								{ 
									clearTimeout(d); 
								} 
								if(a)
								{ 
									d=setTimeout(function()
									{ 
										x(false); 
									} 
									,_7.wait); 
								} 
							} 
							,o=function(x,a)
							{ 
								return _euc(x)+"="+_euc(a)+"; 
									"+w(); 
							} 
							,n=1,h=function(x,z)
							{ 
								if(typeof x=="object")
								{ 
									x=_7.util.toKV(x); 
								} 
								var a=(x||"").split("?"),x=a.shift(),y=(a.pop()||"").split("&"); 
								return z(x,y); 
							} 
							,k=function(a,x,z,y)
							{ 
								if(!x)
								{ 
									x=
									{ 
									} 
									; 
								} 
								if(!x.remove)
								{ 
									x.remove=[]; 
								} 
								if(x.remove.push)
								{ 
									x.remove.push("sms_ss"); 
									x.remove.push("at_xt"); 
									x.remove.push("fb_ref"); 
									x.remove.push("fb_source"); 
								} 
								if(x.remove)
								{ 
									a=t(a,x.remove); 
								} 
								if(x.clean)
								{ 
									a=l(a); 
								} 
								if(x.defrag)
								{ 
									a=e(a); 
								} 
								if(x.add)
								{ 
									a=m(a,x.add,z,y); 
								} 
								return a; 
							} 
							,m=function(z,B,A,x)
							{ 
								var a=
								{ 
								} 
								; 
								if(B)
								{ 
									for(var y in B)
									{ 
										if(z.indexOf(y+"=")>-1)
										{ 
											continue; 
										} 
										a[y]=p(B[y],z,A,x); 
									} 
									B=_7.util.toKV(a); 
								} 
								return z+(B.length?((z.indexOf("?")>-1?"&":"?")+B):""); 
							} 
							,p=function(y,x,z,a)
							{ 
								var z=z||addthis_share; 
								return y.replace(/\
								{ 
									\
									{ 
										service\} 
									\} 
								/g,_euc(a||"")).replace(/\
								{ 
									\
									{ 
										code\} 
									\} 
								/g,_euc(a||"")).replace(/\
								{ 
									\
									{ 
										title\} 
									\} 
								/g,_euc(z.title)).replace(/\
								{ 
									\
									{ 
										url\} 
									\} 
								/g,_euc(x)); 
							} 
							,t=function(x,z)
							{ 
								var a=
								{ 
								} 
								,z=z||[]; 
								for(var y=0; 
									y<z.length; 
									y++)
								{ 
									a[z[y]]=1; 
								} 
								return h(x,function(A,D)
								{ 
									var E=[]; 
									if(D)
									{ 
										for(var B in D)
										{ 
											if(typeof(D[B])=="string")
											{ 
												var C=(D[B]||"").split("="); 
												if(C.length!=2&&D[B])
												{ 
													E.push(D[B]); 
												} 
												else
												{ 
													if(a[C[0]])
													{ 
														continue; 
													} 
													else
													{ 
														if(D[B])
														{ 
															E.push(D[B]); 
														} 
													} 
												} 
											} 
										} 
										A+=(E.length?("?"+E.join("&")):""); 
									} 
									return A; 
								} 
								); 
							} 
							,q=function(a)
							{ 
								var x=a.split("#").pop().split(",").shift().split("=").pop(); 
								if(_7.util.ivc(x))
								{ 
									return a.split("#").pop().split(","); 
								} 
								return[""]; 
							} 
							,e=function(a)
							{ 
								var x=q(a).shift().split("=").pop(); 
								if(_7.util.ivc(x))
								{ 
									return a.split("#").shift(); 
								} 
								else
								{ 
									x=a.split("#").slice(1).join("#").split("; 
										").shift(); 
										if(x.split(".").length==3)
										{ 
											x=x.split(".").slice(0,-1).join("."); 
										} 
										if(x.length==12&&x.substr(0,1)=="."&&(/[a-zA-Z0-9\-_]
										{ 
											11} 
										/).test(x.substr(1)))
										{ 
											return a.split("#").shift(); 
										} 
								} 
								return a; 
							} 
							,l=function(a)
							{ 
								return h(a,function(y,B)
								{ 
									var x=y.indexOf("; 
										jsessionid"),C=[]; 
										if(x>-1)
										{ 
											y=y.substr(0,x); 
										} 
										if(B)
										{ 
											for(var z in B)
											{ 
												if(typeof(B[z])=="string")
												{ 
													var A=(B[z]||"").split("="); 
													if(A.length==2)
													{ 
														if(A[0].indexOf("utm_")===0||A[0]=="gclid"||A[0]=="sms_ss"||A[0]=="at_xt"||A[0]=="fb_ref"||A[0]=="fb_source")
														{ 
															continue; 
														} 
													} 
													if(B[z])
													{ 
														C.push(B[z]); 
													} 
												} 
											} 
											y+=(C.length?("?"+C.join("&")):""); 
										} 
										return y; 
								} 
								); 
							} 
							,b=function()
							{ 
								var a=(typeof(v.pub||"")=="function"?v.pub():v.pub)||"unknown"; 
								return"AT-"+a+"/-/"+v.ab+"/"+i()+"/"+(n++)+(v.uid!==null?"/"+v.uid:""); 
							} 
							; 
							if(!_7.track)
							{ 
								_7.track=
								{ 
								} 
								; 
							} 
							f.util.extend(_7.track,
							{ 
fcv:o,ran:r,rup:t,aup:m,cof:e,gof:q,clu:l,mgu:k,ssid:i,sta:b,sxm:c} 
								); 
						} 
						)(_7,_7.api,_7); 
						(function(c,e,i)
						{ 
							var n=".",h="; 
								",s=".",l=n.length,k=0,q=
							{ 
wpp:1,blg:1} 
								; 
								function b(t)
								{ 
									var u=t.split("; 
										").shift(); 
										if(u.split(".").length==3)
										{ 
											u=u.split(".").slice(0,-1).join("."); 
										} 
										if(u.length==12&&u.substr(0,1)=="."&&(/[a-zA-Z0-9\-_]
										{ 
											11} 
										/).test(u.substr(1)))
										{ 
											return 1; 
										} 
										return 0; 
								} 
								function r(t)
								{ 
									return(t.length==(11+l)&&(t.substr(0,l)==n)&&(/[a-zA-Z0-9\-_]
									{ 
										11} 
									/).test(t.substr(l))); 
								} 
								function o(u)
								{ 
									var t=_7.util.atohb(u.substr(l)); 
									return
									{ 
id:(t.substr(0,8)+"00000000,"+parseInt(t.substr(16),10)),fuid:t.substr(8,8)} 
										; 
								} 
								function g(O,M)
								{ 
									if(!O)
									{ 
										O=document.location; 
									} 
									if(!M)
									{ 
										M=d.referer||d.referrer||""; 
									} 
									var N,U,E,S,w,I,z=0,A=0,K=O?O.href:"",G=(K||"").split("#").shift(),v=O.hash.substr(1),J=_7.util.ghp(O.search,1),L=_7.util.ghp(O.hash),A=0,D=L.at_st,Q=L.at_pco,w=J.sms_ss,C=J.fb_ref,t=J.at_xt,x=J.at_st; 
									if(!D)
									{ 
										if(r(v))
										{ 
											var V=_7.util.atohb(v.substr(l)); 
											I=V.substr(8,8); 
											D=V.substr(0,8)+"00000000,"; 
											D+=parseInt(V.substr(16),10); 
										} 
									} 
									if(C&&!D)
									{ 
										var R=s,F=C.split(R); 
										if(F.length<2&&C.indexOf("_")>-1)
										{ 
											R="_"; 
											F=C.split(R); 
										} 
										var y=F.length>1?F.pop():"",u=F.join(R); 
										if(!r(u))
										{ 
											u=C; 
											y=""; 
										} 
										if(r(u))
										{ 
											var V=_7.util.atohb(u.substr(l)); 
											t=V.substr(0,16)+","+parseInt(V.substr(16),10); 
											w="facebook_"+(y||"like"); 
										} 
										else
										{ 
											var T=C.split("=").pop().split(s); 
											if(T.length==2&&_7.util.ivc(T[0]))
											{ 
												t=T.join(","); 
												w="facebook_"+(y||"like"); 
											} 
										} 
									} 
									D=(D&&_7.util.ivc(D.split(",").shift()))?D:""; 
									if(!t)
									{ 
										var R=(v.indexOf(h)>-1)?h:s,B=v.substr(l).split(R); 
										if(B.length==2&&r(v.substr(0,1)+B[0]))
										{ 
											var V=_7.util.atohb(B[0]); 
											t=V.substr(0,16)+","+parseInt(V.substr(16),10); 
											w=B[1]; 
											z=1; 
										} 
									} 
									if(Q)
									{ 
										E=1; 
									} 
									if(D)
									{ 
										A=parseInt(D.split(",").pop())+1; 
										U=D.split(",").shift(); 
									} 
									else
									{ 
										if(K.indexOf(_atd+"book")==-1&&G!=M)
										{ 
											var H=[],P; 
											if(t)
											{ 
												P=t.split(","); 
												N=_duc(P.shift()); 
												if(N.indexOf(",")>-1)
												{ 
													P=N.split(","); 
													N=P.shift(); 
												} 
											} 
											else
											{ 
												if(x)
												{ 
													P=x.split(","); 
													S=_duc(P.shift()); 
													if(S.indexOf(",")>-1)
													{ 
														P=S.split(","); 
														S=P.shift(); 
													} 
												} 
											} 
											if(P&&P.length)
											{ 
												A=Math.min(3,parseInt(P.pop())+1); 
											} 
										} 
									} 
									if(!_7.util.ivc(U))
									{ 
										U=null; 
									} 
									if(!_7.util.ivc(S))
									{ 
										S=null; 
									} 
									w=(w||"").split("#").shift().split("?").shift(); 
									return
									{ 
rsi:U,cfc:E,hash:z,rsiq:S,fuid:I,rxi:N,rsc:w,gen:A} 
										; 
								} 
								function f(v,t)
								{ 
									if(!t||(t.data_track_clickback!==false&&t.data_track_linkback!==false))
									{ 
										if(k)
										{ 
											return true; 
										} 
										if(_atc.ver>=250)
										{ 
											return(k=true); 
										} 
										v=(v||window.addthis_product||"").split(","); 
										for(var u=0; 
											u<v.length; 
											u++)
										{ 
											if(q[v[u].split("-").shift()])
											{ 
												return(k=true); 
											} 
										} 
									} 
									return false; 
								} 
								function j(t,u)
								{ 
									t=t||a.util.cuid(); 
									return n+_7.util.hbtoa(t+Math.min(3,u||0)); 
								} 
								function p(u,v,t)
								{ 
									t=t||a.util.cuid(); 
									return u.indexOf("#")>-1?u:u+"#"+j((v?t:t.substr(0,8)+_7.gub()),(a.smd||
									{ 
									} 
									).gen)+(v?s+v:""); 
								} 
								function m(v)
								{ 
									var u,x,z,A; 
									if(v.indexOf("#")>-1)
									{ 
										var y=v.split("#").slice(1).join("#"); 
										if(b(y))
										{ 
											var t=y.substr(1).split("."),w=(t.length)?t.shift():""; 
											x=(t.length)?t.pop():""; 
											if(w)
											{ 
												w=_7.util.atohb(w); 
												u=w.substr(0,16); 
												z=parseInt(w.substr(16),10); 
												if(!isNaN(z))
												{ 
													A=A||
													{ 
													} 
													; 
													A.gen=z; 
												} 
											} 
											if(_7.util.ivc(u))
											{ 
												A=A||
												{ 
												} 
												; 
												A.xid=u; 
											} 
											if(x.search(/^[a-zA-Z0-9_]+$/)!=-1)
											{ 
												A=A||
												{ 
												} 
												; 
												A.rsc=x; 
											} 
										} 
									} 
									return A; 
								} 
								_7.extend(_7.track,
								{ 
cur:p,dcu:m,gcc:j,cpf:n,ctp:f,eop:g,ich:b} 
									); 
						} 
						)(_7,_7.api,_7); 
						(function(b,d,c)
						{ 
							function f(g)
							{ 
								if(g=="t.co")
								{ 
									return"twitter"; 
								} 
								var h,i; 
								for(h in b.services.map)
								{ 
									i=b.services.map[h]; 
									if(i==="")
									{ 
										i=h+".com"; 
									} 
									if(g.indexOf(i)!=-1)
									{ 
										return h; 
									} 
								} 
								return; 
							} 
							function e(h)
							{ 
								var i,k,j,g; 
								h=_duc(h); 
								h=h.toLowerCase(); 
								h=h.replace(/[,; 
								:\+\|]/g," "); 
								h=h.replace(/[^a-z0-9. '\-]/g,""); 
									h=h.replace(/\s+/g," "); 
								h=h.replace(/\s+$/g,""); 
								k=[]; 
								j=h.split(" "); 
								for(g=0; 
									g<j.length; 
									g++)
								{ 
									i=j[g]; 
									if(i.charAt(0)=="-")
									{ 
										continue; 
									} 
									else
									{ 
										if(/'s$/.test(i))
										{ 
											k.push(i.substring(0,i.length-2).replace(/[-']/g,"")+"'s"); 
										} 
										else
										{ 
											k=k.concat(i.replace(/'/g,"").split("-")); 
										} 
									} 
								} 
								return k; 
							} 
							function a()
							{ 
								var h=b.dr,l=b.ad.clr(h),i=
								{ 
								} 
								,j,k,g; 
								if(typeof(h)=="undefined"||h==="")
								{ 
									i.type="direct"; 
									return i; 
								} 
								j=b.util.host(h); 
								k=f(j); 
								if(typeof(k)!="undefined")
								{ 
									i.type="social"; 
									i.service=k; 
								} 
								else
								{ 
									if(b.ad.iss(h))
									{ 
										i.type="search"; 
										i.domain=b.util.host(h); 
										g=b.ad.fst(h); 
										i.terms=e(g); 
									} 
									else
									{ 
										if(l&b.ad.ref.r_ondomain)
										{ 
											i.type="internal"; 
											i.domain=document.location.hostname; 
										} 
										else
										{ 
											if(l&b.ad.ref.r_offdomain)
											{ 
												i.type="referred"; 
												i.domain=b.util.host(h); 
											} 
											else
											{ 
												i.type="direct"; 
											} 
										} 
									} 
								} 
								return i; 
							} 
							if(!b.track)
							{ 
								b.track=
								{ 
								} 
								; 
							} 
							b.track.ts=
							{ 
get:a,gst:e} 
								; 
						} 
						)(_7,_7.api,_7); 
						(function()
						{ 
							var d=document,a=_7,_193=0,cvt=[],avt=null,_196=
							{ 
ftho:1,aqe3:1,d99r:1,neud:1,"8elu":1,bqfn:1} 
								,_197=Math.random()<_atc.csmp,_198=Math.random()<1000*_atc.csmp,_199=new RegExp(/\(?(\d
								{ 
									3} 
								)\)?[- ]?(\d
								{ 
									3} 
								)[- ]?(\d
								{ 
									4} 
								)/g),_19a=new RegExp(/^((([a-z]|[0-9]|\-)+)\.)+([a-z])+$/ig),qtp=[],xtp=function()
								{ 
									var p; 
									while(p=qtp.pop())
									{ 
										trk(p); 
									} 
								} 
								,atf=null,pcs=[],spc=null; 
								function apc(c)
								{ 
									c=c.split("-").shift(); 
									for(var i=0; 
										i<pcs.length; 
										i++)
									{ 
										if(pcs[i]==c)
										{ 
											return; 
										} 
									} 
									pcs.push(c); 
								} 
								function get_atssh()
								{ 
									var div=d.getElementById("_atssh"); 
									if(!div)
									{ 
										div=d.ce("div"); 
										div.style.visibility="hidden"; 
										div.id="_atssh"; 
										a.opp(div.style); 
										d.body.insertBefore(div,d.body.firstChild); 
									} 
									return div; 
								} 
								function ctf(url)
								{ 
									var ifr,r=Math.floor(Math.random()*1000),div=get_atssh(); 
									if(!a.bro.msi)
									{ 
										ifr=d.ce("iframe"); 
										ifr.id="_atssh"+r; 
										ifr.title="AddThis utility frame"; 
									} 
									else
									{ 
										if(a.bro.ie6&&!url&&d.location.protocol.indexOf("https")==0)
										{ 
											url="javascript:''"; 
										} 
										div.innerHTML="<iframe id=\"_atssh"+r+"\" width=\"1\" height=\"1\" title=\"AddThis utility frame\" name=\"_atssh"+r+"\" "+(url?"src=\""+url+"\"":"")+">"; 
										ifr=d.getElementById("_atssh"+r); 
									} 
									a.opp(ifr.style); 
									ifr.frameborder=ifr.style.border=0; 
									ifr.style.top=ifr.style.left=0; 
									return ifr; 
								} 
								function jsl()
								{ 
									var w=window; 
									return((((w.jQuery||
									{ 
									} 
									).fn||
									{ 
									} 
									).jquery&&1)|((w.Prototype||
									{ 
									} 
									).Version&&2)|((w.YUI||
									{ 
									} 
									).version||(w.YAHOO||
									{ 
									} 
									).VERSION&&4)|((w.Ext||
									{ 
									} 
									).version&&8)|((w.dojo||
									{ 
									} 
									).version&&16)|((w._gaq||w._gat)&&32)|(w.google_ad_client&&64)|((w.FB||w.fbAsyncInit)&&128)|(w.$BTB&&256)|(w.meebo&&512)|(w.gigya&&1024)|(w.SHARETHIS&&2048)|(w._qevents&&4096)|(w.twttr&&8192)); 
								} 
								function onMenuShare(e)
								{ 
									var _1a9=300; 
									if(e&&e.data&&e.data.service)
									{ 
										if(a.dcp>=_1a9)
										{ 
											return; 
										} 
										trk(
										{ 
gen:(e.data.service.indexOf("facebook")>-1||e.data.service=="more"||e.data.service=="settings")?-1:_1a9,pix:"dest="+e.data.service,svc:e.data.service,url:(e.data.url||null)} 
											); 
											a.dcp=_1a9; 
									} 
								} 
								var _1aa,_1ab=[]; 
								function onApiUsage(evt)
								{ 
									if(evt.data.call)
									{ 
										_1ab.push(evt.data.call); 
									} 
									if(!_1aa)
									{ 
										_1aa=setTimeout(function()
										{ 
											img("ap","3","calls="+_euc(_1ab.join(",")),
											{ 
											} 
											); 
										} 
										,10000); 
									} 
								} 
								function onMenuPop(evt)
								{ 
									var t=
									{ 
									} 
									,data=evt.data||
									{ 
									} 
									,svc=data.svc,pco=data.pco,_1b2=data.cmo,_1b3=data.crs,_1b4=data.cso; 
									if(svc)
									{ 
										t.sh=svc; 
									} 
									if(_1b2)
									{ 
										t.cm=_1b2; 
									} 
									if(_1b4)
									{ 
										t.cs=1; 
									} 
									if(_1b3)
									{ 
										t.cr=1; 
									} 
									if(pco)
									{ 
										t.spc=pco; 
									} 
									img("sh","3",null,t); 
								} 
								function trk(t,_1b6)
								{ 
									var dr=a.dr,rev=(a.rev||""); 
									if(!t)
									{ 
										return; 
									} 
									t.xck=_atc.xck?1:0; 
									t.xxl=1; 
									t.sid=a.track.ssid(); 
									t.pub=a.pub(); 
									t.ssl=a.ssl||0; 
									t.srl=_atc.lamp; 
									t.du=a.tru(t.url||a.du||a.dl.href); 
									t.xtr=_1b6!==undefined?0:_atc.xtr; 
									if(a.dt)
									{ 
										t.dt=a.dt; 
									} 
									if(a.cb)
									{ 
										t.cb=a.cb; 
									} 
									if(a.kw)
									{ 
										t.kw=a.kw; 
									} 
									t.lng=a.lng(); 
									t.ver=_atc.ver; 
									t.jsl=a.track.jsl(); 
									if(!a.upm&&a.uid)
									{ 
										t.uid=a.uid; 
									} 
									t.pc=t.spc||pcs.join(","); 
									if(dr)
									{ 
										t.dr=a.tru(dr); 
									} 
									if(a.dh)
									{ 
										t.dh=a.dh; 
									} 
									if(rev)
									{ 
										t.rev=rev; 
									} 
									if(a.xfr)
									{ 
										if(a.upm)
										{ 
											if(atf)
											{ 
												atf.contentWindow.postMessage(_31(t),"*"); 
											} 
										} 
										else
										{ 
											var div=get_atssh(),base=_atc.rsrcs.sh+(false?"?t="+new Date().getTime():""); 
											if(atf)
											{ 
												div.removeChild(div.firstChild); 
											} 
											atf=ctf(); 
											atf.src=base+"#"+_31(t); 
											div.appendChild(atf); 
										} 
									} 
									else
									{ 
										qtp.push(t); 
									} 
								} 
								function img(i,c,x,obj,_1bf)
								{ 
									if(!window.at_sub&&!_atc.xtr)
									{ 
										var t=obj||
										{ 
										} 
										; 
										t.evt=i; 
										if(x)
										{ 
											t.ext=x; 
										} 
										avt=t; 
										if(_1bf===1)
										{ 
											xmi(true); 
										} 
										else
										{ 
											a.track.sxm(true,xmi); 
										} 
									} 
								} 
								function cev(k,v)
								{ 
									cvt.push(a.track.fcv(k,v)); 
									a.track.sxm(true,xmi); 
								} 
								function xmi(_1c3)
								{ 
									var h=a.dl?a.dl.hostname:""; 
									if(cvt.length>0||avt)
									{ 
										a.track.sxm(false,xmi); 
										if(_atc.xtr)
										{ 
											return; 
										} 
										var t=avt||
										{ 
										} 
										; 
										t.ce=cvt.join(","); 
										cvt=[]; 
										avt=null; 
										trk(t); 
										if(_1c3)
										{ 
											var i=d.ce("iframe"); 
											i.id="_atf"; 
											_7.opp(i.style); 
											d.body.appendChild(i); 
											i=d.getElementById("_atf"); 
										} 
									} 
								} 
								function onCopy()
								{ 
									var text="",_1c8=250; 
									if(window.getSelection)
									{ 
										text=_7.trim((window.getSelection().toString()||"")).replace(_199," ").replace(/[\b]+/g," ").split(" "); 
										if(text.length)
										{ 
											if(_197&&_193<3)
											{ 
												cev("cbc",text.length); 
											} 
											_193++; 
											if(!_198)
											{ 
												return; 
											} 
											var _1c9=[]; 
											for(var i=0; 
												i<text.length; 
												i++)
											{ 
												if(text[i]&&text[i].length<=50&&text[i].indexOf("@")==-1&&text[i].indexOf("://")==-1&&(!(_19a.test(text[i]))))
												{ 
													_1c9.push(text[i]); 
												} 
											} 
											if(_1c9.length&&_1c9.length<=5&&(!a.dcp||a.dcp<_1c8))
											{ 
												setTimeout(function()
												{ 
													trk(
													{ 
gen:_1c8,pix:"tt="+_euc(_1c9.join(" "))} 
														); 
														a.dcp=_1c8; 
												} 
												,Math.random()*10000); 
											} 
										} 
									} 
								} 
								_7.ed.addEventListener("addthis-internal.params.loaded",function()
								{ 
									var tc=(w.addthis_config||
									{ 
									} 
									).data_track_textcopy; 
									_198=tc!==false&&(_198||((!_7.sub&&((dl||
									{ 
									} 
									).href||"").indexOf(".addthis.com")>-1)||_196[_7.mun(_7.pub())])||(w.addthis_config||
									{ 
									} 
									).data_track_textcopy||(window.addthis_product||"").indexOf("wpp")>-1||(window.addthis_product||"").indexOf("blg")>-1); 
									try
									{ 
										if(_197||_198)
										{ 
											if(a.bro.msi)
											{ 
												document.body.attachEvent("oncopy",onCopy,true); 
											} 
											else
											{ 
												document.addEventListener("copy",onCopy,true); 
											} 
										} 
									} 
									catch(e)
									{ 
									} 
								} 
								); 
								a.ed.addEventListener("addthis-internal.api",onApiUsage); 
								a.ed.addEventListener("addthis-internal.compact",onMenuPop); 
								a.ed.addEventListener("addthis.menu.share",onMenuShare); 
								if(!a.track)
								{ 
									a.track=
									{ 
									} 
									; 
								} 
								a.util.extend(a.track,
								{ 
pcs:pcs,apc:apc,cev:cev,ctf:ctf,jsl:jsl,gtf:get_atssh,qtp:function(p)
	{ 
		qtp.push(p); 
	} 
	,stf:function(f)
	{ 
		atf=f; 
	} 
	,trk:trk,xtp:xtp} 
								); 
						} 
						)(); 
						_23(_7,
						{ 
_rec:[],xfr:!_7.upm||!_7.bro.ffx,pmh:function(e)
	 { 
		 if(e.origin.slice(-12)==".addthis.com")
		 { 
			 if(!e.data)
			 { 
				 return; 
			 } 
			 var data=_7.util.rfromKV(e.data),r=_7._rec; 
			 for(var n=0; 
				 n<r.length; 
				 n++)
			 { 
				 r[n](data); 
			 } 
		 } 
	 } 
						} 
						); 
						_23(_7,
						{ 
lng:function()
	{ 
		return window.addthis_language||(window.addthis_config||
		{ 
		} 
		).ui_language||(_7.bro.msi?navigator.userLanguage:navigator.language)||"en"; 
	} 
	,iwb:function(l)
	{ 
		var wd=
		{ 
th:1,pl:1,sl:1,gl:1,hu:1,is:1,nb:1,se:1,su:1,sw:1} 
			; 
			return!!wd[l]; 
	} 
	,gfl:function(l)
	{ 
		var map=
		{ 
ca:"es",cs:"CZ",cy:"GB",da:"DK",de:"DE",eu:"ES",ck:"US",en:"US",es:"LA",fb:"FI",gl:"ES",ja:"JP",ko:"KR",nb:"NO",nn:"NO",sv:"SE",ku:"TR",zh:"CN","zh-tr":"CN","zh-hk":"HK","zh-tw":"TW",fo:"FO",fb:"LT",af:"ZA",sq:"AL",hy:"AM",be:"BY",bn:"IN",bs:"BA",nl:"NL",et:"EE",fr:"FR",ka:"GE",el:"GR",gu:"IN",hi:"IN",ga:"IE",jv:"ID",kn:"IN",kk:"KZ",la:"VA",li:"NL",ms:"MY",mr:"IN",ne:"NP",pa:"IN",pt:"PT",rm:"CH",sa:"IN",sr:"RS",sw:"KE",tl:"PH",ta:"IN",pl:"PL",tt:"RU",te:"IN",ml:"IN",uk:"UA",vi:"VN",tr:"TR",xh:"ZA",zu:"ZA",km:"KH",tg:"TJ",he:"IL",ur:"PK",fa:"IR",yi:"DE",gn:"PY",qu:"PE",ay:"BO",se:"NO",ps:"AF",tl:"ST"} 
			,rv=map[l]||map[l.split("-").shift()]; 
			if(rv)
			{ 
				return l.split("-").shift()+"_"+rv; 
			} 
			else
			{ 
				return"en_US"; 
			} 
	} 
	,ivl:function(l)
	{ 
		var lg=
		{ 
af:1,afr:"af",ar:1,ara:"ar",az:1,aze:"az",be:1,bye:"be",bg:1,bul:"bg",bn:1,ben:"bn",bs:1,bos:"bs",ca:1,cat:"ca",cs:1,ces:"cs",cze:"cs",cy:1,cym:"cy",da:1,dan:"da",de:1,deu:"de",ger:"de",el:1,gre:"el",ell:"ell",en:1,eo:1,es:1,esl:"es",spa:"spa",et:1,est:"et",eu:1,fa:1,fas:"fa",per:"fa",fi:1,fin:"fi",fo:1,fao:"fo",fr:1,fra:"fr",fre:"fr",ga:1,gae:"ga",gdh:"ga",gl:1,glg:"gl",gu:1,he:1,heb:"he",hi:1,hin:"hin",hr:1,ht:1,hy:1,cro:"hr",hu:1,hun:"hu",id:1,ind:"id",is:1,ice:"is",it:1,ita:"it",ja:1,jpn:"ja",km:1,ko:1,kor:"ko",ku:1,lb:1,ltz:"lb",lt:1,lit:"lt",lv:1,lav:"lv",mk:1,mac:"mk",mak:"mk",ml:1,mn:1,ms:1,msa:"ms",may:"ms",nb:1,nl:1,nla:"nl",dut:"nl",no:1,nds:1,nn:1,nno:"no",oc:1,oci:"oc",pl:1,pol:"pl",ps:1,pt:1,por:"pt",ro:1,ron:"ro",rum:"ro",ru:1,rus:"ru",sk:1,slk:"sk",slo:"sk",sl:1,slv:"sl",sq:1,alb:"sq",sr:1,se:1,si:1,ser:"sr",su:1,sv:1,sve:"sv",sw:1,swe:"sv",ta:1,tam:"ta",te:1,teg:"te",th:1,tha:"th",tl:1,tgl:"tl",tn:1,tr:1,tur:"tr",tpi:1,tt:1,uk:1,ukr:"uk",ur:1,urd:"ur",vi:1,vec:1,vie:"vi","zh-cn":1,"zh-hk":1,"chi-hk":"zh-hk","zho-hk":"zh-hk","zh-tr":1,"chi-tr":"zh-tr","zho-tr":"zh-tr","zh-tw":1,"chi-tw":"zh-tw","zho-tw":"zh-tw",zh:1,chi:"zh",zho:"zh"} 
			; 
			if(lg[l])
			{ 
				return lg[l]; 
			} 
			l=l.split("-").shift(); 
			if(lg[l])
			{ 
				if(lg[l]===1)
				{ 
					return l; 
				} 
				else
				{ 
					return lg[l]; 
				} 
			} 
			return 0; 
	} 
	,ggl:function(l)
	{ 
		var map=
		{ 
en:"en-US",ar:"ar",ca:"ca",zh:"zh-CN",hr:"hr",cs:"cs",da:"da",nl:"nl",et:"et",fi:"fi",fr:"fr",de:"de",el:"el",he:"iw",hi:"hi",hu:"hu",id:"id",it:"it",ja:"ja",ko:"ko",lv:"lv",lt:"lt",ms:"ms",no:"no",fa:"fa",pl:"pl",pt:"pt-BR",ro:"ro",ru:"ru",sr:"sr",sk:"sk",sl:"sl",es:"es",sv:"sv",th:"th",tr:"tr",uk:"uk",vi:"vi"} 
			; 
			return map[l]||null; 
	} 
	,gvl:function(l)
	{ 
		var rv=_7.ivl(l)||"en"; 
		if(rv===1)
		{ 
			rv=l; 
		} 
		return rv; 
	} 
	,alg:function(al,f)
	{ 
		var l=_7.gvl((al||_7.lng()).toLowerCase()); 
		if(l.indexOf("en")!==0&&(!_7.pll||f))
		{ 
			_7.pll=_7.ajs("static/r07/lang16/"+l+".js"); 
		} 
	} 
						} 
						); 
						_23(_7,
						{ 
trim:function(s,e)
	 { 
		 if(s&&s.trim&&typeof(s.trim)=="function")
		 { 
			 s=s.trim(); 
		 } 
		 try
		 { 
			 s=s.replace(/^[\s\u3000]+/,"").replace(/[\s\u3000]+$/,""); 
		 } 
		 catch(exc)
		 { 
		 } 
		 if(s&&e)
		 { 
			 s=_euc(s); 
		 } 
		 return s||""; 
	 } 
	 ,trl:[],tru:function(u,k)
	 { 
		 var rv="",_1e4=0,_1e5=-1; 
		 if(u)
		 { 
			 rv=u.substr(0,300); 
			 if(rv!==u)
			 { 
				 if((_1e5=rv.lastIndexOf("%"))>=rv.length-4)
				 { 
					 rv=rv.substr(0,_1e5); 
				 } 
				 if(rv!=u)
				 { 
					 for(var i in _7.trl)
					 { 
						 if(_7.trl[i]==k)
						 { 
							 _1e4=1; 
						 } 
					 } 
					 if(!_1e4)
					 { 
						 _7.trl.push(k); 
					 } 
				 } 
			 } 
		 } 
		 return rv; 
	 } 
	 ,opp:function(st)
	 { 
		 st.width=st.height="1px"; 
		 st.position="absolute"; 
		 st.zIndex=100000; 
	 } 
	 ,jlr:
	 { 
	 } 
	 ,ajs:function(name,_1e9,_1ea,id,el,_1ed)
	 { 
		 if(!_7.jlr[name]||_1ed)
		 { 
			 var o=d.ce("script"),head=(el)?el:d.gn("head")[0]||d.documentElement; 
			 o.setAttribute("type","text/javascript"); 
			 if(_1ea)
			 { 
				 o.setAttribute("async","true"); 
			 } 
			 if(id)
			 { 
				 o.setAttribute("id",id); 
			 } 
			 o.src=(_1e9?"":_atr)+name; 
			 head.insertBefore(o,head.firstChild); 
			 _7.jlr[name]=1; 
			 return o; 
		 } 
		 return 1; 
	 } 
	 ,jlo:function()
	 { 
		 try
		 { 
			 var a=_7,al=a.lng(),aig=function(src)
			 { 
				 var img=new Image(); 
				 _7.imgz.push(img); 
				 img.src=src; 
			 } 
			 ; 
			 a.alg(al); 
			 if(!a.pld)
			 { 
				 if(a.bro.ie6)
				 { 
					 aig(_atc.rsrcs.widgetpng); 
					 aig(_atr+"static/t00/logo1414.gif"); 
					 aig(_atr+"static/t00/logo88.gif"); 
					 if(window.addthis_feed)
					 { 
						 aig("static/r05/feed00.gif",1); 
					 } 
				 } 
				 if(a.pll&&!window.addthis_translations)
				 { 
					 setTimeout(function()
					 { 
						 a.pld=a.ajs(_atc.rsrcs.menujs); 
					 } 
					 ,10); 
				 } 
				 else
				 { 
					 a.pld=a.ajs(_atc.rsrcs.menujs); 
				 } 
			 } 
		 } 
		 catch(e)
		 { 
		 } 
	 } 
	 ,ao:function(elt,pane,iurl,_1f8,_1f9,_1fa)
	 { 
		 _7.lad(["open",elt,pane,iurl,_1f8,_1f9,_1fa]); 
		 _7.jlo(); 
		 return false; 
	 } 
	 ,ac:function()
	 { 
	 } 
	 ,as:function(s,cf,sh)
	 { 
		 _7.lad(["send",s,cf,sh]); 
		 _7.jlo(); 
	 } 
						} 
						); 
						(function(e,f,k)
						{ 
							var p=document,n=1,a=["cbea","cbeab","kkk","zvys","phz","gvgf","shpxf","chfflyvcf","pernzcvr","svfgvat","wvmm","fcybbtr","flovna"],g=a.length,j=[],c=
							{ 
							} 
							; 
							function b(d)
							{ 
								return d.replace(/[a-zA-Z]/g,function(i)
								{ 
									return String.fromCharCode((i<="Z"?90:122)>=(i=i.charCodeAt(0)+13)?i:i-26); 
								} 
								); 
							} 
							while(g--)
							{ 
								c[b(a[g])]=1; 
							} 
							function h(d)
							{ 
								var i=0; 
								if(!d||typeof(d)!="string")
								{ 
									return i; 
								} 
								d=((d||"").toLowerCase()+"").replace(/ /g,""); 
								if(d=="mature"||d=="adult"||d=="rta-5042-1996-1400-1577-rta")
								{ 
									i|=n; 
								} 
								return i; 
							} 
							function o(t)
							{ 
								var v=0; 
								if(!t||typeof(t)!="string")
								{ 
									return v; 
								} 
								t=((t||"").toLowerCase()+"").replace(/[^a-zA-Z]/g," ").split(" "); 
								for(var d=0,u=t.length; 
									d<u; 
									d++)
								{ 
									if(c[t[d]])
									{ 
										v|=n; 
										return v; 
									} 
								} 
								return v; 
							} 
							function q()
							{ 
								var v=(w.addthis_title||p.title),i=o(v),u=p.all?p.all.tags("META"):p.getElementsByTagName?p.getElementsByTagName("META"):new Array(),t=(u||"").length; 
								if(u&&t)
								{ 
									while(t--)
									{ 
										var d=u[t]||
										{ 
										} 
										,y=(d.name||(d.getAttribute?d.getAttribute("property"):"")||"").toLowerCase(),x=d.content; 
										if(y=="description"||y=="keywords")
										{ 
											i|=o(x); 
										} 
										if(y=="rating")
										{ 
											i|=h(x); 
										} 
										if(y=="keywords"&&x&&x.length)
										{ 
											m(x); 
										} 
									} 
								} 
								return i; 
							} 
							function m(y)
							{ 
								var x=y.split(","),t,d=200; 
								for(var u=0; 
									u<x.length; 
									u++)
								{ 
									t=_7.trim(x[u]); 
									if((d-=(t.length+1))>0)
									{ 
										j.push(t); 
									} 
									else
									{ 
										break; 
									} 
								} 
							} 
							function l()
							{ 
								var x=[],v=p.all?p.all.tags("META"):p.getElementsByTagName?p.getElementsByTagName("META"):new Array(),i=(v||"").length; 
								if(v&&i)
								{ 
									while(i--)
									{ 
										var d=v[i]||
										{ 
										} 
										,z=((d.getAttribute?d.getAttribute("property"):"")||d.name||"").toLowerCase(),y=d.content,u; 
										if(z.indexOf("og:")===0)
										{ 
											u=z.split(":").pop(); 
											if(x.length<7)
											{ 
												x.push(u=="type"?u+"="+y:u); 
											} 
										} 
									} 
								} 
								return x; 
							} 
							function s()
							{ 
								var v=
								{ 
								} 
								,t="",u=p.all?p.all.tags("META"):p.getElementsByTagName?p.getElementsByTagName("META"):new Array(); 
								if(!u||u.length==0)
								{ 
									return v; 
								} 
								for(var d=0; 
									d<u.length; 
									d++)
								{ 
									t=u[d].getAttribute("property")||""; 
									if(t.search(/^og:/i)!=-1)
									{ 
										v[t.replace("og:","")]=u[d].content; 
									} 
								} 
								return _31(v); 
							} 
							function r()
							{ 
								return j.join(","); 
							} 
							if(!e.ad)
							{ 
								e.ad=
								{ 
								} 
								; 
							} 
							_7.extend(e.ad,
							{ 
cla:q,gog:l,og:s,kw:r} 
								); 
						} 
						)(_7,_7.api,_7); 
						(function(c,f,i)
						{ 
							var g=0,b=1,a=2,h=4; 
							function d(m,l,k)
							{ 
								k=(k===undefined||k)||(window.location.protocol=="https:"); 
								l=_7.util.host(l===undefined?window.location.href:l); 
								var o=g; 
								if(m)
								{ 
									var n=_7.util.host(m); 
									if(l==n)
									{ 
										o|=a; 
									} 
									else
									{ 
										o|=h; 
									} 
								} 
								if(!k&&j(m))
								{ 
									o|=b; 
								} 
								return o; 
							} 
							function j(k)
							{ 
								var m=".com/"; 
								var l=0; 
								if(k&&k.match(/ws\/results\/(Web|Images|Video|News)/))
								{ 
									l=1; 
								} 
								else
								{ 
									if(k&&k.indexOf("addthis"==-1)&&(k.match(/google.*\/(search|url|m\?)/)||k.indexOf(m+"url")>-1||k.indexOf("/search?")>-1||k.indexOf(m+"search")>-1||k.indexOf(m+"s?bs")>-1||k.indexOf(m+"s?wd")>-1||k.indexOf(m+"web")>-1||k.match(/aol.*\/aol/)||k.indexOf("hotbot"+m)>-1))
									{ 
										if(e(k)!=false)
										{ 
											l=1; 
										} 
									} 
								} 
								if(l)
								{ 
									return true; 
								} 
								else
								{ 
									return false; 
								} 
							} 
							function e(k)
							{ 
								var m=k.split("?").pop().toLowerCase().split("&"),l,n=/^(?:q|search|bs|wd|p|query|qry|text)=(.*)/; 
								for(l=0; 
									l<m.length; 
									l++)
								{ 
									if(matches=n.exec(m[l]))
									{ 
										return matches[1]; 
									} 
								} 
								return false; 
							} 
							if(!c.ad)
							{ 
								c.ad=
								{ 
								} 
								; 
							} 
							c.ad.clr=d; 
							c.ad.iss=j; 
							c.ad.fst=e; 
							c.ad.ref=
							{ 
r_direct:g,r_search:b,r_ondomain:a,r_offdomain:h} 
								; 
						} 
						)(_7,_7.api,_7); 
						(function(d,e,g)
						{ 
							var i=d,f=[],h=!_7.upm||(_7.dat||
							{ 
							} 
							).rdy; 
							if(!i.du)
							{ 
								i.du=document.location.href; 
							} 
							if(!i.dh)
							{ 
								i.dh=document.location.hostname; 
							} 
							if(!i.dr)
							{ 
								i.dr=document.referrer; 
							} 
							function c(a)
							{ 
								if(h)
								{ 
									setTimeout(function()
									{ 
										_7.track.trk(a,true); 
									} 
									,(!_7.upm?_7.wait*2:0)); 
								} 
								else
								{ 
									f.push(a); 
								} 
							} 
							function b(l)
							{ 
								var n=
								{ 
pco:"cnv-100"} 
									,a=
									{ 
pxid:1,ev:1} 
										; 
										if(l)
										{ 
											for(var m in l)
											{ 
												if(a[m])
												{ 
													n[m]=l[m]; 
												} 
											} 
										} 
										c(
										{ 
gen:2000,fcp:1,pix:i.util.toKV(n)} 
											); 
							} 
							function j(a)
							{ 
								c(
								{ 
pixu:a} 
									); 
							} 
							if(!d.ad)
							{ 
								d.ad=
								{ 
								} 
								; 
							} 
							_7.extend(d.ad,
							{ 
								event:b,getPixels:j} 
							); 
							_7.ed.addEventListener("addthis-internal.data.rdy",function()
							{ 
								h=1; 
								for(var a=0; 
									a<f.length; 
									a++)
								{ 
									c(f[a]); 
								} 
							} 
							); 
						} 
						)(_7,_7.api,_7); 
						(function(f,g,h)
						{ 
							var c,j=document,m=f.util,b=f.event.EventDispatcher,k=25,e=[]; 
							function i(p,r,o)
							{ 
								var d=[]; 
								function d()
								{ 
									d.push(arguments); 
								} 
								function q()
								{ 
									o[p]=r; 
									while(d.length)
									{ 
										r.apply(o,d.shift()); 
									} 
								} 
								d.ready=q; 
								return d; 
							} 
							function l(p)
							{ 
								if(p&&p instanceof a)
								{ 
									e.push(p); 
								} 
								for(var d=0; 
									d<e.length; 
									)
								{ 
									var o=e[d]; 
									if(o&&o.test())
									{ 
										e.splice(d,1); 
										a.fire("load",o,
										{ 
resource:o} 
											); 
									} 
									else
									{ 
										d++; 
									} 
								} 
								if(e.length)
								{ 
									setTimeout(l,k); 
								} 
							} 
							function a(r,o,q)
							{ 
								var d=this,p=new b(d); 
								p.decorate(p).decorate(d); 
								this.ready=false; 
								this.loading=false; 
								this.id=r; 
								this.url=o; 
								if(typeof(q)==="function")
								{ 
									this.test=q; 
								} 
								else
								{ 
									this.test=function()
									{ 
										return(!!_window[q]); 
									} 
									; 
								} 
								a.addEventListener("load",function(s)
								{ 
									var t=s.resource; 
									if(!t||t.id!==d.id)
									{ 
										return; 
									} 
									d.loading=false; 
									d.ready=true; 
									p.fire(s.type,t,
									{ 
resource:t} 
										); 
								} 
								); 
							} 
							m.extend(a.prototype,
							{ 
load:function()
	 { 
		 if(!this.loading)
		 { 
			 var d; 
			 if(this.url.substr(this.url.length-4)==".css")
			 { 
				 var o=(j.gn("head")[0]||j.documentElement); 
				 d=j.ce("link"); 
				 d.rel="stylesheet"; 
				 d.type="text/css"; 
				 d.href=this.url; 
				 d.media="all"; 
				 o.insertBefore(d,o.firstChild); 
			 } 
			 else
			 { 
				 d=_7.ajs(this.url,1); 
			 } 
			 this.loading=true; 
			 a.monitor(this); 
			 return d; 
		 } 
		 else
		 { 
			 return 1; 
		 } 
	 } 
							} 
							); 
							var n=new b(a); 
							n.decorate(n).decorate(a); 
							m.extend(a,
							{ 
known:
							{ 
							} 
							,loading:e,monitor:l} 
							); 
							f.resource=
							{ 
Resource:a,ApiQueueFactory:i} 
								; 
						} 
						)(_7,_7.api,_7); 
						(function(c,s,u)
						{ 
							var w=document,g=
							{ 
							} 
							,f=
							{ 
							} 
							,l,v=[],b=0,q=0,r=0,i=true,y=0,t=0,h=(w.domain.search(/\.addthis\.com$/i)!=-1&&w.location.href.indexOf("381242-url-title")==-1)?1:0; 
							function n()
							{ 
								return((_atc.ltj&&j()&&k())||(o()&&FB.XFBML&&FB.XFBML.parse)); 
							} 
							function k()
							{ 
								if(l===undefined)
								{ 
									try
									{ 
										var z=(document.getElementsByTagName("html"))[0]; 
										if(z)
										{ 
											if(z.getAttribute&&z.getAttribute("xmlns:fb"))
											{ 
												l=true; 
											} 
											else
											{ 
												if(_7.bro.msi)
												{ 
													var d=z.outerHTML.substr(0,z.outerHTML.indexOf(">")); 
													if(d.indexOf("xmlns:fb")>-1)
													{ 
														l=true; 
													} 
												} 
											} 
										} 
									} 
									catch(A)
									{ 
										l=false; 
									} 
								} 
								return l; 
							} 
							function o()
							{ 
								return(typeof(window.FB)=="object"&&FB.Event&&typeof(FB.Event.subscribe)=="function"); 
							} 
							function j()
							{ 
								return!window.FB_RequireFeatures&&(!window.FB||(!FB.Share&&!FB.Bootstrap)); 
							} 
							function e()
							{ 
								var d,z; 
								if(w.location.href.indexOf(_atr)==-1&&!_7.sub&&!b)
								{ 
									if(o())
									{ 
										z=(addthis_config.data_ga_tracker||addthis_config.data_ga_property); 
										b=1; 
										FB.Event.subscribe("message.send",function(B)
										{ 
											var A=
											{ 
											} 
											,C=f[B]; 
											for(d in addthis_share)
											{ 
												A[d]=addthis_share[d]; 
											} 
											if(C)
											{ 
												for(d in C)
												{ 
													A[d]=C[d]; 
												} 
											} 
											A.url=B; 
											_7.share.track("facebook_send",0,A,addthis_config); 
											if(z)
											{ 
												_7.gat("facebook_send",B,addthis_config,A); 
											} 
										} 
										); 
										FB.Event.subscribe("edge.create",function(B)
										{ 
											if(!g[B])
											{ 
												var A=
												{ 
												} 
												,C=f[B]; 
												for(d in addthis_share)
												{ 
													A[d]=addthis_share[d]; 
												} 
												if(C)
												{ 
													for(d in C)
													{ 
														A[d]=C[d]; 
													} 
												} 
												A.url=B; 
												_7.share.track("facebook_like",0,A,addthis_config); 
												if(z)
												{ 
													_7.gat("facebook_like",B,addthis_config,A); 
												} 
												g[B]=1; 
											} 
										} 
										); 
										FB.Event.subscribe("edge.remove",function(B)
										{ 
											if(g[B])
											{ 
												var A=
												{ 
												} 
												,C=f[B]; 
												for(d in addthis_share)
												{ 
													A[d]=addthis_share[d]; 
												} 
												if(C)
												{ 
													for(d in C)
													{ 
														A[d]=C[d]; 
													} 
												} 
												A.url=B; 
												_7.share.track("facebook_unlike",0,A,addthis_config); 
												g[B]=0; 
											} 
										} 
										); 
										FB.Event.subscribe("comment.create",function(B)
										{ 
											var A=
											{ 
											} 
											,C=f[B.href]; 
											for(d in addthis_share)
											{ 
												A[d]=addthis_share[d]; 
											} 
											if(C)
											{ 
												for(d in C)
												{ 
													A[d]=C[d]; 
												} 
											} 
											A.url=B.href; 
											_7.share.track("facebook_comment",0,A,addthis_config); 
											if(z)
											{ 
												_7.gat("facebook_comment",B.href,addthis_config,A); 
											} 
										} 
										); 
										FB.Event.subscribe("comment.remove",function(B)
										{ 
											var A=
											{ 
											} 
											,C=f[B.href]; 
											for(d in addthis_share)
											{ 
												A[d]=addthis_share[d]; 
											} 
											if(C)
											{ 
												for(d in C)
												{ 
													A[d]=C[d]; 
												} 
											} 
											A.url=B.href; 
											_7.share.track("facebook_uncomment",0,A,addthis_config); 
										} 
										); 
									} 
									else
									{ 
										if(window.fbAsyncInit&&!r)
										{ 
											if(q<3)
											{ 
												setTimeout(e,3000+1000*2*(q++)); 
											} 
											r=1; 
										} 
									} 
								} 
							} 
							function p(d,C)
							{ 
								var B="fb-root",A=w.getElementById(B),z=window.fbAsyncInit; 
								v.push(d); 
								if(o()&&FB.XFBML&&FB.XFBML.parse)
								{ 
									FB.XFBML.parse(d); 
									e(); 
								} 
								else
								{ 
									if(!z)
									{ 
										if(!A)
										{ 
											A=w.ce("div"); 
											A.id=B; 
											document.body.appendChild(A); 
										} 
										if(!z)
										{ 
											var D=w.createElement("script"); 
											D.src=w.location.protocol+"//connect.facebook.net/"+(C||_7.gfl(_7.lng()))+"/all.js"; 
											D.async=true; 
											A.appendChild(D); 
											z=function()
											{ 
												FB.init(
												{ 
appId:h?"140586622674265":"172525162793917",status:true,cookie:true} 
													); 
											} 
											; 
										} 
									} 
									if(i)
									{ 
										i=false; 
										window.__orig__fbAsyncInit=z; 
										window.fbAsyncInit=function()
										{ 
											window.__orig__fbAsyncInit(); 
											for(var E=0; 
												E<v.length; 
												E++)
											{ 
												FB.XFBML.parse(v[E]); 
											} 
											e(); 
										} 
										; 
									} 
								} 
							} 
							function m(G,E)
							{ 
								if(G.ost)
								{ 
									return; 
								} 
								var C,z,F=_7.api.ptpa(G,"fb:subscribe"),A="",D=F.layout||"button_count",d=
								{ 
standard:[450,F.show_faces?80:35],button_count:[90,25],box_count:[55,65]} 
									,H=F.width||(d[D]?d[D][0]:100),B=F.height||(d[D]?d[D][1]:25); 
									passthrough=_7.util.toKV(F); 
									_7.ufbl=1; 
									if(n())
									{ 
										if(F.layout===undefined)
										{ 
											F.layout="button_count"; 
										} 
										if(F.show_faces===undefined)
										{ 
											F.show_faces="false"; 
										} 
										if(F.action===undefined)
										{ 
											F.action="subscribe"; 
										} 
										if(F.width===undefined)
										{ 
											F.width=H; 
										} 
										if(F.font===undefined)
										{ 
											F.font="arial"; 
										} 
										if(F.href===undefined)
										{ 
											F.href=_7.track.mgu(E.share.url,
											{ 
defrag:1} 
												); 
										} 
										for(z in F)
										{ 
											A+=" "+z+"=\""+F[z]+"\""; 
										} 
										if(!E.share.xid)
										{ 
											E.share.xid=_7.util.cuid(); 
										} 
										f[F.href]=
										{ 
										} 
										; 
										for(z in E.share)
										{ 
											f[F.href][z]=E.share[z]; 
										} 
										G.innerHTML="<fb:subscribe ref=\""+_7.share.gcp(E.share,E.conf,".sub").replace(",","_")+"\" "+A+"></fb:subscribe>"; 
										p(G); 
									} 
									else
									{ 
										if(!_7.bro.msi)
										{ 
											C=w.ce("iframe"); 
										} 
										else
										{ 
											G.innerHTML="<iframe frameborder=\"0\" scrolling=\"no\" allowTransparency=\"true\" scrollbars=\"no\""+(_7.bro.ie6?" src=\"javascript:''\"":"")+"></iframe>"; 
											C=G.firstChild; 
										} 
										C.style.overflow="hidden"; 
										C.style.scrolling="no"; 
										C.style.scrollbars="no"; 
										C.style.border="none"; 
										C.style.borderWidth="0px"; 
										C.style.width=H+"px"; 
										C.style.height=B+"px"; 
										C.src="//www.facebook.com/plugins/subscribe.php?href="+_euc(_7.track.mgu(E.share.url,
										{ 
defrag:1} 
											))+"&layout=button_count&show_faces=false&width=100&action=subscribe&font=arial&"+passthrough; 
											if(!_7.bro.msi)
											{ 
												G.appendChild(C); 
											} 
									} 
									G.noh=G.ost=1; 
							} 
							function x(G,E)
							{ 
								if(G.ost)
								{ 
									return; 
								} 
								var H,A,d,F=_7.api.ptpa(G,"fb:like"),B="",D=F.layout||"button_count",z=
								{ 
standard:[450,F.show_faces?80:35],button_count:[90,25],box_count:[55,65]} 
									,I=F.width||(z[D]?z[D][0]:100),C=F.height||(z[D]?z[D][1]:25); 
									passthrough=_7.util.toKV(F); 
									_7.ufbl=1; 
									if(n())
									{ 
										if(F.layout===undefined)
										{ 
											F.layout="button_count"; 
										} 
										if(F.show_faces===undefined)
										{ 
											F.show_faces="false"; 
										} 
										if(F.action===undefined)
										{ 
											F.action="like"; 
										} 
										if(F.width===undefined)
										{ 
											F.width=I; 
										} 
										if(F.font===undefined)
										{ 
											F.font="arial"; 
										} 
										if(F.href===undefined)
										{ 
											d=_7.util.clone(E.share.url_transforms||
											{ 
											} 
											); 
											d.defrag=1; 
											F.href=_7.track.mgu(E.share.url,d); 
										} 
										for(A in F)
										{ 
											B+=" "+A+"=\""+F[A]+"\""; 
										} 
										if(!E.share.xid)
										{ 
											E.share.xid=_7.util.cuid(); 
										} 
										f[F.href]=
										{ 
										} 
										; 
										for(A in E.share)
										{ 
											f[F.href][A]=E.share[A]; 
										} 
										G.innerHTML="<fb:like ref=\""+_7.share.gcp(E.share,E.conf,".like").replace(",","_")+"\" "+B+"></fb:like>"; 
										p(G); 
									} 
									else
									{ 
										if(!_7.bro.msi)
										{ 
											H=w.ce("iframe"); 
										} 
										else
										{ 
											G.innerHTML="<iframe frameborder=\"0\" scrolling=\"no\" allowTransparency=\"true\" scrollbars=\"no\""+(_7.bro.ie6?" src=\"javascript:''\"":"")+"></iframe>"; 
											H=G.firstChild; 
										} 
										H.style.overflow="hidden"; 
										H.style.scrolling="no"; 
										H.style.scrollbars="no"; 
										H.style.border="none"; 
										H.style.borderWidth="0px"; 
										H.style.width=I+"px"; 
										H.style.height=C+"px"; 
										H.src="//www.facebook.com/plugins/like.php?href="+_euc(_7.track.mgu(E.share.url,
										{ 
defrag:1} 
											))+"&layout=button_count&show_faces=false&width=100&action=like&font=arial&"+passthrough; 
											if(!_7.bro.msi)
											{ 
												G.appendChild(H); 
											} 
									} 
									G.noh=G.ost=1; 
							} 
							function a(D,B,F,z)
							{ 
								var E=(D.passthrough||
								{ 
								} 
								).facebook||
								{ 
								} 
								,C=
								{ 
								} 
								,d,A=y?("http://www.facebook.com/sharer.php?&t="+_euc(D.title)+"&u="+_euc(_7.share.acb("facebook",D,B))):(t?("http://www.facebook.com/connect/prompt_feed.php?message="+_euc(D.title)+"%0A%0D"+_euc(_7.share.acb("facebook",D,B))):h?"http://www.facebook.com/dialog/feed?redirect_uri="+_euc("http://s7.addthis.com/static/postshare/c00.html")+"&app_id=140586622674265&link="+_euc(_7.share.acb("facebook",D,B))+"&name="+_euc(D.title)+"&description="+_euc(D.description||""):_7.share.genurl("facebook",0,D,B)); 
								if(y||t||h)
								{ 
									for(d in B)
									{ 
										C[d]=B[d]; 
									} 
									C.hdl=1; 
									_7.share.track("facebook",0,D,C,1); 
								} 
								if(B.ui_use_same_window||z)
								{ 
									window.location.href=A; 
								} 
								else
								{ 
									window.open(A,"_blank"); 
								} 
								return false; 
							} 
							c.share=c.share||
							{ 
							} 
							; 
							c.share.fb=
							{ 
like:x,subs:m,has:o,ns:k,ready:n,compat:j,share:a,sub:e,load:p} 
								; 
						} 
						)(_7,_7.api,_7); 
						(function(e,o,r)
						{ 
							var t=document,x=e,i=[],b=n(); 
							function n()
							{ 
								var d=t.gn("link"),B=
								{ 
								} 
								; 
								for(var A=0; 
									A<d.length; 
									A++)
								{ 
									var a=d[A]; 
									if(a.href&&a.rel)
									{ 
										B[a.rel]=a.href; 
									} 
								} 
								return B; 
							} 
							function v()
							{ 
								var a=t.location.protocol; 
								if(a=="file:")
								{ 
									a="http:"; 
								} 
								return a+"//"+_atd; 
							} 
							function l(B,C,A,a)
							{ 
								if(B=="more"&&_atc.ver>=300)
								{ 
									var d=_7.util.clone(A||(typeof _atw==="undefined"?addthis_share:_atw.share)); 
									d.url=_euc(d.url); 
									d.title=_euc(d.title||(addthis_share||
									{ 
									} 
									).title||""); 
									return _atr+"static/r07/bookmark004.html#ats="+_euc(_7.util.rtoKV(d))+"&atc="+_euc(_7.util.rtoKV((typeof _atw==="undefined"?a:_atw.config))); 
								} 
								return v()+(C?"feed.php":(B=="email"&&_atc.ver>=300?"tellfriend.php":"bookmark.php"))+"?v="+(_atc.ver)+"&winname=addthis&"+z(B,C,A,a)+(x.dr?"&pre="+_euc(x.track.cof(x.dr)):"")+"&tt=0"+(B==="more"&&x.bro.ipa?"&imore=1":"")+(x.bro.msi?"&captcha_provider=recaptcha":""); 
							} 
							function z(R,G,U,Z)
							{ 
								var N=x.trim,W=window,S=x.pub(),L=window._atw||
								{ 
								} 
								,M=(U&&U.url?U.url:(L.share&&L.share.url?L.share.url:(W.addthis_url||W.location.href))),Y,F=function(ac)
								{ 
									if(M&&M!="")
									{ 
										var d=M.indexOf("#at"+ac); 
										if(d>-1)
										{ 
											M=M.substr(0,d); 
										} 
									} 
								} 
								; 
								if(!Z)
								{ 
									Z=L.conf||
									{ 
									} 
									; 
								} 
								else
								{ 
									for(var T in L.conf)
									{ 
										if(!(Z[T]))
										{ 
											Z[T]=L.conf[T]; 
										} 
									} 
								} 
								if(!U)
								{ 
									U=L.share||
									{ 
									} 
									; 
								} 
								else
								{ 
									for(var T in L.share)
									{ 
										if(!(U[T]))
										{ 
											U[T]=L.share[T]; 
										} 
									} 
								} 
								if(x.rsu())
								{ 
									U.url=window.addthis_url; 
									U.title=window.addthis_title; 
									M=U.url; 
								} 
								if(!S||S=="undefined")
								{ 
									S="unknown"; 
								} 
								Y=Z.services_custom; 
								F("pro"); 
								F("opp"); 
								F("cle"); 
								F("clb"); 
								F("abc"); 
								if(M.indexOf("addthis.com/static/r07/ab")>-1)
								{ 
									M=M.split("&"); 
									for(var V=0; 
										V<M.length; 
										V++)
									{ 
										var P=M[V].split("="); 
										if(P.length==2)
										{ 
											if(P[0]=="url")
											{ 
												M=P[1]; 
												break; 
											} 
										} 
									} 
								} 
								if(Y instanceof Array)
								{ 
									for(var V=0; 
										V<Y.length; 
										V++)
									{ 
										if(Y[V].code==R)
										{ 
											Y=Y[V]; 
											break; 
										} 
									} 
								} 
								var X=((U.templates&&U.templates[R])?U.templates[R]:""),A=((U.modules&&U.modules[R])?U.modules[R]:""),D=U.share_url_transforms||U.url_transforms||
								{ 
								} 
								,J=U.track_url_transforms||U.url_transforms,ab=((D&&D.shorten&&U.shorteners)?(typeof(D.shorten)=="string"?D.shorten:(D.shorten[R]||D.shorten["default"]||"")):""),H="",Q=(Z.product||W.addthis_product||("men-"+_atc.ver)),B=L.crs,I="",O=x.track.gof(M),aa=O.length==2?O.shift().split("=").pop():"",a=O.length==2?O.pop():"",K=(Z.data_track_clickback||Z.data_track_linkback||!S||S=="AddThis")||(Z.data_track_clickback!==false&&_atc.ver>=250); 
								if(U.email_vars)
								{ 
									for(var T in U.email_vars)
									{ 
										I+=(I==""?"":"&")+_euc(T)+"="+_euc(U.email_vars[T]); 
									} 
								} 
								if(x.track.spc&&Q.indexOf(x.track.spc)==-1)
								{ 
									Q+=","+x.track.spc; 
								} 
								if(D&&D.shorten&&U.shorteners)
								{ 
									for(var T in U.shorteners)
									{ 
										for(var C in U.shorteners[T])
										{ 
											H+=(H.length?"&":"")+_euc(T+"."+C)+"="+_euc(U.shorteners[T][C]); 
										} 
									} 
								} 
								M=x.track.cof(M); 
								M=x.track.mgu(M,D,U,R); 
								if(J)
								{ 
									U.trackurl=x.track.mgu(U.trackurl||M,J,U,R); 
								} 
								var E="pub="+S+"&source="+Q+"&lng="+(x.lng()||"xx")+"&s="+R+(Z.ui_508_compliant?"&u508=1":"")+(G?"&h1="+N((U.feed||U.url).replace("feed://",""),1)+"&t1=":"&url="+N(M,1)+"&title=")+N(U.title||W.addthis_title,1)+(_atc.ver<200?"&logo="+N(W.addthis_logo,1)+"&logobg="+N(W.addthis_logo_background,1)+"&logocolor="+N(W.addthis_logo_color,1):"")+"&ate="+x.track.sta()+((R!="email"||_atc.ver<300)?"&frommenu=1":"")+((window.addthis_ssh&&(!B||addthis_ssh!=B)&&(addthis_ssh==R||addthis_ssh.search(new RegExp("(?:^|,)("+R+")(?:$|,)"))>-1))?"&ips=1":"")+(B?"&cr="+(R==B?1:0):"")+"&uid="+_euc(x.uid&&x.uid!="x"?x.uid:x.util.cuid())+(U.email_template?"&email_template="+_euc(U.email_template):"")+(I?"&email_vars="+_euc(I):"")+(ab?"&shortener="+_euc(typeof(ab)=="array"?ab.join(","):ab):"")+(ab&&H?"&"+H:"")+((U.passthrough||
								{ 
								} 
								)[R]?"&passthrough="+N((typeof(U.passthrough[R])=="object"?x.util.toKV(U.passthrough[R]):U.passthrough[R]),1):"")+(U.description?"&description="+N(U.description,1):"")+(U.html?"&html="+N(U.html,1):(U.content?"&html="+N(U.content,1):""))+(U.trackurl&&U.trackurl!=M?"&trackurl="+N(U.trackurl,1):"")+(U.screenshot?"&screenshot="+N(U.screenshot,1):"")+(U.screenshot_secure?"&screenshot_secure="+N(U.screenshot_secure,1):"")+(U.swfurl?"&swfurl="+N(U.swfurl,1):"")+(U.swfurl_secure?"&swfurl_secure="+N(U.swfurl_secure,1):"")+(Z.hdl?"&hdl=1":"")+(x.cb?"&cb="+x.cb:"")+(x.ufbl?"&ufbl=1":"")+(x.uud?"&uud=1":"")+(U.iframeurl?"&iframeurl="+N(U.iframeurl,1):"")+(U.width?"&width="+U.width:"")+(U.height?"&height="+U.height:"")+(Z.data_track_p32?"&p32="+Z.data_track_p32:"")+(K||_7.track.ctp(Z.product,Z)?"&ct=1":"")+((K||_7.track.ctp(Z.product,Z))&&M.indexOf("#")>-1?"&uct=1":"")+((Y&&Y.url)?"&acn="+_euc(Y.name)+"&acc="+_euc(Y.code)+"&acu="+_euc(Y.url):"")+(x.smd?(x.smd.rxi?"&rxi="+x.smd.rxi:"")+(x.smd.rsi?"&rsi="+x.smd.rsi:"")+(x.smd.gen?"&gen="+x.smd.gen:""):((aa?"&rsi="+aa:"")+(a?"&gen="+a:"")))+(U.xid?"&xid="+N(U.xid,1):"")+(X?"&template="+N(X,1):"")+(A?"&module="+N(A,1):"")+(Z.ui_cobrand?"&ui_cobrand="+N(Z.ui_cobrand,1):"")+(R=="email"&&_atc.ver>=300?"&ui_email_from="+N(Z.ui_email_from,1)+"&ui_email_note="+N(Z.ui_email_note,1):"")+(_atc.ver<300?((Z.ui_header_color?"&ui_header_color="+N(Z.ui_header_color,1):"")+(Z.ui_header_background?"&ui_header_background="+N(Z.ui_header_background,1):"")):""); 
								return E; 
							} 
							function y(A,d,B)
							{ 
								var a=A.xid; 
								if(d.data_track_clickback||d.data_track_linkback||_7.track.ctp(d.product,d))
								{ 
									return x.track.gcc(a,(x.smd||
									{ 
									} 
									).gen||0)+(B||""); 
								} 
								else
								{ 
									return""; 
								} 
							} 
							function q(G,I,C,H,d,J)
							{ 
								var F=x.pub(),a=H||I.url||"",B=I.xid||x.util.cuid(),D=(C.data_track_clickback||C.data_track_linkback||!F||F=="AddThis")||(C.data_track_clickback!==false&&_atc.ver>=250); 
								if(a.toLowerCase().indexOf("http%3a%2f%2f")===0)
								{ 
									a=_duc(a); 
								} 
								if(d)
								{ 
									var A=
									{ 
									} 
									; 
									for(var E in I)
									{ 
										A[E]=I[E]; 
									} 
									A.xid=B; 
									setTimeout(function()
									{ 
										(new Image()).src=l(G=="twitter"&&J?"tweet":G,0,A,C); 
									} 
									,100); 
								} 
								return(D?x.track.cur(a,G,B):a); 
							} 
							function g(C,A,a)
							{ 
								var A=A||
								{ 
								} 
								,B=C.share_url_transforms||C.url_transforms||
								{ 
								} 
								,d=x.track.cof(x.track.mgu(C.url,B,C,"mailto")); 
								return"mailto:?subject="+_euc(C.title?C.title:d)+"&body="+_euc(q("mailto",C,A,d,a)); 
							} 
							function h(a)
							{ 
								return((!a.templates||!a.templates.twitter)&&(!x.wlp||x.wlp=="http:")); 
							} 
							function f(d,B,I,A)
							{ 
								var G=B||550,C=I||450,H=screen.width,E=screen.height,F=Math.round((H/2)-(G/2)),a=0,D; 
								if(E>C)
								{ 
									F=Math.round((E/2)-(C/2)); 
								} 
								w.open(d,(_7.bro.msi?"":(A||"addthis_share")),"left="+F+",top="+a+",width="+G+",height="+C+",personalbar=no,toolbar=no,scrollbars=yes,location=yes,resizable=yes"); 
								return false; 
							} 
							function u(d,A,a)
							{ 
								w.open(l(d,0,A,a),"addthis_share"); 
								return false; 
							} 
							function j(d)
							{ 
								var a=
								{ 
twitter:1,wordpress:1,email:_atc.ver>=300,more:_atc.ver>=300,raiseyourvoice:1,vk:1} 
									; 
									return a[d]; 
							} 
							function p(F,E,B,D,a,A)
							{ 
								var C=
								{ 
wordpress:
								{ 
width:720,height:570} 
									,linkedin:
									{ 
width:600,height:400} 
										,email:_atc.ver>=300?
										{ 
width:660,height:660} 
											:
	  { 
width:735,height:450} 
		  ,more:_atc.ver>=300?
		  { 
width:660,height:716} 
			  :
	  { 
width:735,height:450} 
		  ,vk:
		  { 
width:720,height:290} 
			  ,raiseyourvoice:
			  { 
width:480,height:635} 
				  ,"default":
				  { 
width:550,height:450} 
								} 
								,d=l(F,0,E,B); 
								if(B.ui_use_same_window)
								{ 
									window.location.href=d; 
								} 
								else
								{ 
									f(d,D||(C[F]||C["default"]).width,a||(C[F]||C["default"]).height,A); 
								} 
								return false; 
							} 
							function c(F,B,G,D)
							{ 
								var C=F.share_url_transforms||F.url_transforms||
								{ 
								} 
								,A,d=(F.passthrough||
								{ 
								} 
								).twitter||
								{ 
								} 
								,a=x.track.cof(x.track.mgu(F.url,C,F,"twitter")),E=((F.passthrough||
								{ 
								} 
								).twitter==undefined)?
								{ 
								} 
								:d; 
								if(!F.templates)
								{ 
									F.templates=
									{ 
									} 
									; 
								} 
								if(!F.templates.twitter)
								{ 
									F.templates.twitter=(F.text||((F.title==t.title)?E.text:F.title)||"
									{ 

										{ 
											title} 
									} 
									:")+" 
									{ 

										{ 
											url} 
									} 
									via @"+(F.via||E.via||"AddThis"); 
								} 
								a=l("twitter",0,F,B); 
								if(A)
								{ 
									F.title=A; 
								} 
								if(B.ui_use_same_window||D)
								{ 
									window.location.href=a; 
								} 
								else
								{ 
									f(a,550,450,"twitter_tweet"); 
								} 
								return false; 
							} 
							function k(B,A,a,d)
							{ 
								_7.ed.fire("addthis.menu.share",window.addthis||
								{ 
								} 
								,
								{ 
element:d||
		{ 
		} 
		,service:B||"unknown",url:A.trackurl||A.url} 
								); 
							} 
							function m(C,D,B,d,A)
							{ 
								var a=l(C,D,B,d); 
								i.push(x.ajs(a,1)); 
								if(!A)
								{ 
									k(C,B,d); 
								} 
							} 
							function s(A,d,a)
							{ 
								return v()+"tellfriend.php?&fromname=aaa&fromemail="+_euc(d.from)+"&frommenu=1&tofriend="+_euc(d.to)+(A.email_template?"&template="+_euc(A.email_template):"")+(d.vars?"&vars="+_euc(d.vars):"")+"&lng="+(x.lng()||"xx")+"&captcha_provider=nucaptcha&note="+_euc(d.note)+"&"+z("email",null,null,a); 
							} 
							e.share=e.share||
							{ 
							} 
							; 
							e.util.extend(e.share,
							{ 
auw:j,ocw:f,stw:p,siw:u,pts:c,unt:h,uadd:z,genurl:l,geneurl:s,genieu:g,acb:q,gcp:y,svcurl:v,track:m,notify:k,links:b} 
								); 
						} 
						)(_7,_7.api,_7); 
						(function(a,b,c)
						{ 
							if(!a.services)
							{ 
								a.services=
								{ 
								} 
								; 
							} 
							a.services.map=
							{ 
facebook:"",twitter:"",reddit:"",stumbleupon:"",gmail:"mail.google.com",blogger:"",linkedin:"",tumblr:"",delicious:"",yahoomail:"compose.mail.yahoo.com",hotmail:"hotmail.msn.com","100zakladok":"100zakladok.ru","2tag":"2tag.nl","2linkme":"","7live7":"",a1webmarks:"a1-webmarks.com",a97abi:"",addio:"add.io",menu:"api.addthis.com",adfty:"",adifni:"",aerosocial:"",allmyfaves:"",amazonwishlist:"amazon.com",amenme:"",aim:"lifestream.aol.com",aolmail:"webmail.aol.com",armenix:"",arto:"",aviary:"",baang:"baang.ir",baidu:"cang.baidu.com",bebo:"",bentio:"",biggerpockets:"",bitly:"bit.ly",bizsugar:"",bleetbox:"",blinklist:"",blip:"blip.pl",bloggy:"bloggy.se",blogmarks:"blogmarks.net",blogtrottr:"",blurpalicious:"",bobrdobr:"bobrdobr.ru",bonzobox:"",socialbookmarkingnet:"social-bookmarking.net",bookmarkycz:"bookmarky.cz",bookmerkende:"bookmerken.de",bordom:"bordom.net",box:"box.net",brainify:"",bryderi:"bryderi.se",buddymarks:"",buzzzy:"",camyoo:"",cardthis:"partner.cardthis.com",care2:"",chiq:"",cirip:"cirip.ro",citeulike:"citeulike.org",classicalplace:"",cndig:"cndig.org",colivia:"colivia.de",technerd:"",connotea:"connotea.org",cootopia:"",cosmiq:"cosmiq.de",curateus:"curate.us",designbump:"",designmoo:"",digthiswebhost:"",digaculturanet:"digacultura.net",digg:"",diggita:"diggita.it",diglog:"",digo:"digo.it",digzign:"",diigo:"",dipdive:"",domelhor:"domelhor.net",dosti:"dosti.webdunia.com",dotnetkicks:"",dotnetshoutout:"",woscc:"wos.cc",douban:"",draugiem:"draugiem.lv",drimio:"",dropjack:"",dwellicious:"",dzone:"",edelight:"edelight.de",efactor:"",ekudos:"ekudos.nl",elefantapl:"elefanta.pl",embarkons:"",eucliquei:"eucliquei.com.br",evernote:"",extraplay:"",ezyspot:"",stylishhome:"",fabulously40:"",informazione:"fai.informazione.it",fark:"",farkinda:"",fashiolista:"",fashionburner:"",favable:"",faves:"",favlogde:"favlog.de",favoritende:"favoriten.de",favoritus:"",flaker:"flaker.pl",flosspro:"floss.pro",folkd:"",formspring:"formspring.me",thefreedictionary:"",fresqui:"",friendfeed:"",friendster:"",funp:"",fwisp:"",gabbr:"",gamekicker:"",givealink:"givealink.org",globalgrind:"",govn:"my.go.vn",goodnoows:"",googletranslate:"translate.google.com",gravee:"",greaterdebater:"",grono:"grono.net",habergentr:"haber.gen.tr",hackernews:"news.ycombinator.com",hadashhot:"hadash-hot.co.il",hatena:"b.hatena.ne.jp",gluvsnap:"healthimize.com",hedgehogs:"hedgehogs.net",hellotxt:"",historious:"historio.us",hitmarks:"",hotbookmark:"hotbmark.com",hotklix:"",w3validator:"validator.w3.org",hyves:"hyves.net",idearef:"",identica:"identi.ca",ihavegot:"",index4:"index4.in",indexor:"indexor.co.uk",instapaper:"",investorlinks:"",iorbix:"",isociety:"isociety.be",iwiw:"iwiw.hu",jamespot:"",jappy:"jappy.de",joliprint:"api.joliprint.com",jumptags:"",zooloo:"kablog.com",kaboodle:"",kaevur:"",kaixin:"kaixin001.com",kindleit:"fivefilters.org",kipup:"",kirtsy:"",kledy:"kledy.de",kommenting:"",latafaneracat:"latafanera.cat",laaikit:"laaik.it",ladenzeile:"ladenzeile.de",librerio:"",linkninja:"linkninja.com.br",linkagogo:"",linksgutter:"",linkshares:"linkshares.net",linkuj:"linkuj.cz",livejournal:"",lockerblogger:"",logger24:"",mymailru:"connect.mail.ru",markme:"markme.me",mashbord:"",mawindo:"",meinvz:"meinvz.net",mekusharim:"mekusharim.walla.co.il",memonic:"",memori:"memori.ru",meneame:"meneame.net",live:"profile.live.com",mindbodygreen:"",misterwong:"mister-wong.com",misterwong_de:"mister-wong.de",moemesto:"moemesto.ru",moikrug:"moikrug.ru",mototagz:"",mrcnetworkit:"mrcnetwork.it",multiply:"",myaol:"favorites.my.aol.com",myhayastan:"myhayastan.am",mylinkvault:"",myspace:"",n4g:"",naszaklasa:"nk.pl",netlog:"",netvibes:"",netvouz:"",newsmeback:"",newstrust:"newstrust.net",newsvine:"",nujij:"nujij.nl",odnoklassniki_ru:"odnoklassniki.ru",oknotizie:"oknotizie.virgilio.it",oneview:"oneview.de",ongobee:"",orkut:"promote.orkut.com",dashboard:"api.addthis.com",oyyla:"",packg:"",pafnetde:"pafnet.de",pdfonline:"savepageaspdf.pdfonline.com",pdfmyurl:"",phonefavs:"",pingfm:"ping.fm",planypus:"planyp.us",plaxo:"",plurk:"",pochvalcz:"pochval.cz",popedition:"",posteezy:"",posterous:"",pratiba:"prati.ba",printfriendly:"",pusha:"pusha.se",qrfin:"qrf.in",quantcast:"",qzone:"sns.qzone.qq.com",readitlater:"readitlaterlist.com",rediff:"share.rediff.com",redkum:"",ridefix:"",scoopat:"scoop.at",scoopit:"scoop.it",sekoman:"sekoman.lv",select2gether:"www2.select2gether.com",shaveh:"shaveh.co.il",shetoldme:"",shirintar:"shir.intar.in",simpy:"",sinaweibo:"v.t.sina.com.cn",slashdot:"slashdot.org",smiru:"smi2.ru",sodahead:"",sonico:"",speedtile:"speedtile.net",sphinn:"",spinsnap:"",spokentoyou:"",sportpost:"",yiid:"spread.ly",springpad:"springpadit.com",squidoo:"",startaid:"",startlap:"startlap.hu",storyfollower:"",studivz:"studivz.net",stuffpit:"",stumpedia:"",stylehive:"",svejo:"svejo.net",symbaloo:"",taaza:"",tagmarksde:"tagmarks.de",tagvn:"",tagza:"",tarpipe:"",tellmypolitician:"",thewebblend:"",thinkfinity:"community.thinkfinity.org",thisnext:"",throwpile:"",tipd:"",topsitelernet:"ekle.topsiteler.net",transferr:"",tuenti:"",tulinq:"",tusul:"",tvinx:"",tweetmeme:"api.tweetmeme.com",twitthis:"",typepad:"",upnews:"upnews.it",urlaubswerkde:"urlaubswerk.de",urlcapt:"",viadeo:"",virb:"",visitezmonsite:"",vk:"vkontakte.ru",vkrugudruzei:"vkrugudruzei.ru",voxopolis:"",vybralisme:"vybrali.sme.sk",vyoom:"",webnews:"webnews.de",domaintoolswhois:"domaintools.com",windows:"api.addthis.com",windycitizen:"",wirefan:"",wordpress:"",worio:"",wykop:"wykop.pl",xanga:"",xing:"",yahoobkm:"bookmarks.yahoo.com",yammer:"",yardbarker:"",yemle:"",yigg:"yigg.de",yoolink:"go.yoolink.to",yorumcuyum:"",youblr:"",youbookmarks:"",youmob:"",yuuby:"",zakladoknet:"zakladok.net",zanatic:"",ziczac:"ziczac.it",zingme:"link.apps.zing.vn",zootool:""} 
								; 
						} 
						)(_7,_7.api,_7); 
						var w=window,ac=w.addthis_config||
						{ 
						} 
						,css=new _7.resource.Resource("widgetcss",_atc.rsrcs.widgetcss,function()
						{ 
							return true; 
						} 
						),_30a=new _7.resource.Resource("widgetIE67css",_atc.rsrcs.widgetIE67css,function()
						{ 
							return true; 
						} 
						),_30b=new _7.resource.Resource("widget32css",_atc.rsrcs.widget32css,function()
						{ 
							return true; 
						} 
						); 
						if(w.addthis&&w.addthis.timer)
						{ 
							w.addthis.timer.core=(new Date()).getTime(); 
						} 
						function main()
						{ 
							if(w.addthis&&w.addthis.timer)
							{ 
								w.addthis.timer.main=(new Date()).getTime(); 
							} 
							try
							{ 
								if(_atc.xol&&!_atc.xcs&&ac.ui_use_css!==false)
								{ 
									css.load(); 
									if(_7.bro.ie6||_7.bro.ie7)
									{ 
										_30a.load(); 
									} 
									if(_7.bro.ipa)
									{ 
										_30b.load(); 
									} 
								} 
								var a=_7,msi=a.bro.msi,hp=0,_30f=window.addthis_config||
								{ 
								} 
								,dt=d.title,dr=(typeof(a.rdr)!=="undefined")?a.rdr:(d.referer||d.referrer||""),du=dl?dl.href:null,dh=dl.hostname,_314=du,_315=0,al=(_7.lng().split("-")).shift(),_317=_7.track.eop(dl,dr),cvt=[],nabc=!!a.cookie.rck("nabc"),cfc=_317.cfc,rsiq=_317.rsiq,rsi=_317.rsi,rxi=_317.rxi,rsc=_317.rsc.split("&").shift().split("%").shift().replace(/[^a-z0-9_]/g,""),gen=_317.gen,fuid=_317.fuid,ifr,_322=_atc.rsrcs.sh+"#",data,_324=function()
								{ 
									if(!_7.track.pcs.length)
									{ 
										_7.track.apc(window.addthis_product||("men-"+_atc.ver)); 
									} 
									data.pc=_7.track.pcs.join(","); 
								} 
								; 
								if(rsc=="tweet")
								{ 
									rsc="twitter"; 
								} 
								if(window.addthis_product)
								{ 
									_7.track.apc(addthis_product); 
									if(addthis_product.indexOf("fxe")==-1&&addthis_product.indexOf("bkm")==-1)
									{ 
										_7.track.spc=addthis_product; 
									} 
								} 
								var l=_7.share.links.canonical; 
								if(l)
								{ 
									if(l.indexOf("http")!==0)
									{ 
										_314=(du||"").split("//").pop().split("/"); 
										if(l.indexOf("/")===0)
										{ 
											_314=_314.shift()+l; 
										} 
										else
										{ 
											_314.pop(); 
											_314=_314.join("/")+"/"+l; 
										} 
										_314=dl.protocol+"//"+_314; 
									} 
									else
									{ 
										_314=l; 
									} 
									_7.usu(0,1); 
								} 
								_314=_314.split("#
								{ 
									").shift(); 
										a.igv(_314,d.title||""); 
									var _326=addthis_share.view_url_transforms||addthis_share.track_url_transforms||addthis_share.url_transforms; 
									if(_326)
									{ 
										_314=_7.track.mgu(_314,_326); 
									} 
									if(rsi)
									{ 
										rsi=rsi.substr(0,8)+fuid; 
									} 
									if(a.bro.mod==-1)
									{ 
										var m=document.compatMode; 
										if(m)
										{ 
											var md=1; 
											if(m=="BackCompat")
											{ 
												md=2; 
											} 
											else
											{ 
												if(m=="CSS1Compat")
												{ 
													md=0; 
												} 
											} 
											a.bro.mode=md; 
											if(a.bro.msi)
											{ 
												a.bro.mod=md; 
											} 
										} 
									} 
									a.smd=
									{ 
rsi:rsi,rxi:rxi,gen:gen,rsc:rsc} 
										; 
										a.dr=a.tru(dr,"fr"); 
										a.du=a.tru(_314,"fp"); 
										a.dt=dt=w.addthis_share.title; 
										a.cb=a.ad.cla(); 
										a.kw=(a.cb!==1?a.ad.kw():""); 
										a.dh=dl.hostname; 
										a.ssl=du&&du.indexOf("https")===0?1:0; 
										data=
										{ 
iit:(new Date()).getTime(),tmr:_31((w.addthis||
	{ 
	} 
	).timer||
	{ 
	} 
	),cb:a.cb,kw:a.kw,ab:a.ab,dh:a.dh,dr:a.dr,du:a.du,dt:dt,md:a.bro.mode,cap:_31(
	{ 
tc:_30f.data_track_textcopy?1:0,ab:_30f.data_track_addressbar?1:0} 
		),inst:a.inst,jsl:a.track.jsl(),lng:a.lng(),ogt:_7.ad.gog().join(","),pc:w.addthis_product||"men",pub:a.pub(),ssl:a.ssl,sid:_7.track.ssid(),srd:_atc.damp,srf:_atc.famp,srp:_atc.pamp,srl:_atc.lamp,srx:_atc.xamp,ver:_atc.ver,xck:_atc.xck||0,xtr:_atc.xtr||0,og:_7.ad.og()} 
										; 
										if(a.dcp==Number.MAX_VALUE)
										{ 
											data.dnp=1; 
										} 
										if(a.pixu)
										{ 
											data.pixu=a.pixu; 
										} 
										if(a.trl.length)
										{ 
											data.trl=a.trl.join(","); 
										} 
										if(a.rev)
										{ 
											data.rev=a.rev; 
										} 
										if(_30f.data_track_clickback||_30f.data_track_linkback||_7.track.ctp(data.pc,_30f))
										{ 
											data.ct=a.ct=1; 
										} 
										if(a.prv)
										{ 
											data.prv=_31(a.prv); 
										} 
										if(rsc)
										{ 
											data.sr=rsc; 
										} 
										if(a.vamp>=0&&!a.sub)
										{ 
											if(cfc)
											{ 
												cvt.push(a.track.fcv("plv",Math.round(1/_atc.vamp))); 
												cvt.push(a.track.fcv("cfc",1)); 
												cvt.push(a.track.fcv("rcf",dl.hash)); 
												data.ce=cvt.join(","); 
											} 
											else
											{ 
												if(rsi&&(fuid!=a.gub()))
												{ 
													cvt.push(a.track.fcv("plv",Math.round(1/_atc.vamp))); 
													cvt.push(a.track.fcv("rsi",rsi)); 
													cvt.push(a.track.fcv("gen",gen)); 
													cvt.push(a.track.fcv("abc",1)); 
													cvt.push(a.track.fcv("fcu",a.gub())); 
													cvt.push(a.track.fcv("rcf",dl.hash)); 
													data.ce=cvt.join(","); 
													_315="addressbar"; 
												} 
												else
												{ 
													if(rxi||rsiq||rsc)
													{ 
														cvt.push(a.track.fcv("plv",Math.round(1/_atc.vamp))); 
														if(rsc)
														{ 
															cvt.push(a.track.fcv("rsc",rsc)); 
														} 
														if(rxi)
														{ 
															cvt.push(a.track.fcv("rxi",rxi)); 
														} 
														else
														{ 
															if(rsiq)
															{ 
																cvt.push(a.track.fcv("rsi",rsiq)); 
															} 
														} 
														if(rsiq||rxi)
														{ 
															cvt.push(a.track.fcv("gen",gen)); 
														} 
														data.ce=cvt.join(","); 
														_315=rsc||"unknown"; 
													} 
												} 
											} 
										} 
										if(_315&&a.bamp>=0)
										{ 
											data.clk=1; 
											if(a.dcp!=Number.MAX_VALUE)
											{ 
												a.dcp=data.gen=50; 
											} 
											_7.ed.fire("addthis.user.clickback",window.addthis||
											{ 
											} 
											,
											{ 
service:_315} 
												); 
										} 
										if(!window.at_noxld)
										{ 
											data.xld=1; 
										} 
										if(a.upm)
										{ 
											data.xd=1; 
										} 
										if(!nabc&&window.history&&typeof(history.replaceState)=="function"&&(!_7.bro.chr||_7.bro.chb)&&(_30f.data_track_addressbar||_30f.data_track_addressbar_paths)&&((du||"").split("#").shift()!=dr)&&(du.indexOf("#")==-1||rsi||(_317.hash&&rxi)))
										{ 
											var path=dl.pathname||"",_32a,_32b=path!="/"; 
											if(_30f.data_track_addressbar_paths)
											{ 
												_32b=0; 
												for(var i=0; 
													i<_30f.data_track_addressbar_paths.length; 
													i++)
												{ 
													_32a=new RegExp(_30f.data_track_addressbar_paths[i].replace(/\*/g,".*")+"$"); 
													if(_32a.test(path))
													{ 
														_32b=1; 
														break; 
													} 
												} 
											} 
											if(_32b&&(!rsi||a.util.ioc(rsi,5)))
											{ 
												history.replaceState(
												{ 
d:(new Date()),g:gen} 
													,d.title,_7.track.cur(dl.href.split("#").shift(),null,_7.track.ssid())); 
											} 
										} 
										if(w.addthis&&w.addthis.timer)
										{ 
											w.addthis.timer.ifr=(new Date()).getTime(); 
											if(data.tmr)
											{ 
												data.tmr+="&ifr="+w.addthis.timer.ifr; 
											} 
										} 
										if(dl.href.indexOf(_atr)==-1&&!a.sub)
										{ 
											if(a.upm)
											{ 
												if(msi)
												{ 
													setTimeout(function()
													{ 
														_324(); 
														ifr=a.track.ctf(_322+_31(data)); 
														a.track.stf(ifr); 
													} 
													,_7.wait); 
													w.attachEvent("onmessage",a.pmh); 
												} 
												else
												{ 
													ifr=a.track.ctf(); 
													w.addEventListener("message",a.pmh,false); 
												} 
												if(_7.bro.ffx)
												{ 
													ifr.src=_322; 
													_7.track.qtp(data); 
												} 
												else
												{ 
													if(!msi)
													{ 
														setTimeout(function()
														{ 
															_324(); 
															ifr.src=_322+_31(data); 
														} 
														,_7.wait); 
													} 
												} 
											} 
											else
											{ 
												ifr=a.track.ctf(); 
												setTimeout(function()
												{ 
													_324(); 
													ifr.src=_322+_31(data); 
												} 
												,_7.wait); 
											} 
											if(ifr)
											{ 
												ifr=a.track.gtf().appendChild(ifr); 
												a.track.stf(ifr); 
											} 
										} 
										if(w.addthis_language||ac.ui_language)
										{ 
											a.alg(); 
										} 
										if(a.plo.length>0)
										{ 
											a.jlo(); 
										} 
								} 
								catch(e)
								{ 
									window.console&&console.log("lod",e); 
								} 
							} 
							w._ate=a; 
							w._adr=r; 
							a._ssc=a._ssh=[]; 
							a.dat=
							{ 
							} 
							; 
							a._rec.push(function(data)
							{ 
								var rdy=a.dat.rdy; 
								_13(data,function(k,v)
								{ 
									a.dat[k]=v; 
								} 
								); 
								if(data.rdy&&!rdy)
								{ 
									a.xfr=1; 
									a.track.xtp(); 
								} 
								if(data.ssc)
								{ 
									a._ssc=data.ssc; 
								} 
								if(data.sshs)
								{ 
									var s=window.addthis_ssh=_duc(data.sshs); 
									a.gssh=1; 
									a._ssh=s.split(","); 
								} 
								if(data.uss)
								{ 
									var u=a._uss=_duc(data.uss).split(","); 
									if(window.addthis_ssh)
									{ 
										var seen=
										{ 
										} 
										,u=u.concat(a._ssh),_334=[]; 
										for(var i=0; 
											i<u.length; 
											i++)
										{ 
											var s=u[i]; 
											if(!seen[s])
											{ 
												_334.push(s); 
											} 
											seen[s]=1; 
										} 
										u=_334; 
									} 
									a._ssh=u; 
									window.addthis_ssh=u.join(","); 
								} 
								if(data.ups)
								{ 
									var s=data.ups.split(","); 
									a.ups=
									{ 
									} 
									; 
									for(var i=0; 
										i<s.length; 
										i++)
									{ 
										if(s[i])
										{ 
											var o=_3f(_duc(s[i])); 
											a.ups[o.name]=o; 
										} 
									} 
									a._ups=a.ups; 
								} 
								if(data.uid)
								{ 
									a.uid=data.uid; 
									_7.ed.fire("addthis-internal.data.uid",
									{ 
									} 
									,
									{ 
uid:data.uid} 
										); 
								} 
								if(data.bti)
								{ 
									a.bti=data.bti; 
									_7.ed.fire("addthis-internal.data.bti",
									{ 
									} 
									,
									{ 
bti:data.bti} 
										); 
								} 
								if(data.bts)
								{ 
									a.bts=parseInt(data.bts); 
									_7.ed.fire("addthis-internal.data.bts",
									{ 
									} 
									,
									{ 
bts:data.bts} 
										); 
								} 
								if(data.vts)
								{ 
									a.vts=parseInt(data.vts); 
									_7.ed.fire("addthis-internal.data.vts",
									{ 
									} 
									,
									{ 
vts:data.vts} 
										); 
								} 
								if(data.geo)
								{ 
									a.geo=(data.geo.constructor=="string")?_7.util.geo.parse(data.geo):data.geo; 
									_7.ed.fire("addthis-internal.data.geo",
									{ 
									} 
									,
									{ 
geo:a.geo} 
										); 
								} 
								if(data.dbm)
								{ 
									a.dbm=data.dbm; 
								} 
								if(data.atgotcode)
								{ 
									a.sau=data.atgotcode; 
								} 
								if(data.rdy&&!rdy)
								{ 
									_7.ed.fire("addthis-internal.data.rdy"); 
									return; 
								} 
							} 
							); 
							try
							{ 
								if(dl.href.indexOf(_atr)>-1)
								{ 
									var ckv=_3f(d.cookie,"; 
										"); 
										a._rec[a._rec.length-1](ckv); 
								} 
								var _338=
								{ 
								} 
								,_339=_7.util.gsp("addthis_widget.js"); 
								if(typeof(_339)=="object")
								{ 
									if(_339.provider)
									{ 
										_338=
										{ 
provider:_7.mun(_339.provider_code||_339.provider),auth:_339.auth||_339.provider_auth||""} 
											; 
											if(_339.uid||_339.provider_uid)
											{ 
												_338.uid=_7.mun(_339.uid||_339.provider_uid); 
											} 
											if(_339.logout)
											{ 
												_338.logout=1; 
											} 
											_7.prv=_338; 
									} 
									if(_339.dnp)
									{ 
										_7.dcp=Number.MAX_VALUE; 
									} 
									if(_339.dnt)
									{ 
										_atc.xtr=1; 
									} 
									if(_339.adurl&&typeof(_339.adurl)=="string")
									{ 
										_7.pixu=_339.adurl; 
									} 
									if(_339.adev&&typeof(_339.adev)=="string")
									{ 
										var ad=_duc(_339.adev).split("; 
											"); 
											_7.ed.addEventListener("addthis-internal.data.uid",function()
										{ 
											for(var i=0; 
												i<ad.length; 
												i++)
											{ 
												var cmds=ad[i].split(","),cmd=
												{ 
												} 
												; 
												for(var j=0; 
													j<cmds.length; 
													j++)
												{ 
													var c=cmds[j].split("="); 
													cmd[c[0]]=c[1]; 
												} 
												if(window.addthis)
												{ 
													addthis.ad.event(cmd); 
												} 
											} 
										} 
										); 
									} 
									if(_339.pubid||_339.pub||_339.username)
									{ 
										w.addthis_pub=_duc(_339.pubid||_339.pub||_339.username); 
									} 
									if(w.addthis_pub&&w.addthis_config)
									{ 
										w.addthis_config.username=w.addthis_pub; 
									} 
									if(_339.domready)
									{ 
										_atc.dr=1; 
									} 
									if(_339.onready&&_339.onready.match(/[a-zA-Z0-9_\.\$]+/))
									{ 
										try
										{ 
											_7.onr=_7.evl(_339.onready); 
										} 
										catch(e)
										{ 
											window.console&&console.log("addthis: onready function ("+_339.onready+") not defined",e); 
										} 
									} 
									if(_339.async)
									{ 
										_atc.xol=1; 
									} 
								} 
								_7.ed.fire("addthis-internal.params.loaded",
								{ 
								} 
								,
								{ 
geo:a.geo} 
									); 
									if((window.addthis_conf||
									{ 
									} 
									).xol)
									{ 
										_atc.xol=1; 
									} 
									if(_atc.ver===120)
									{ 
										var rc="atb"+_7.util.cuid(),_341=_7.util.gst("addthis_widget"),span=d.ce("span"); 
										span.id=rc; 
										_341.parentNode.appendChild(span); 
										_7.igv(); 
										_7.lad(["span",rc,addthis_share.url||"[url]",addthis_share.title||"[title]"]); 
									} 
									if(w.addthis_clickout)
									{ 
										_7.lad(["cout"]); 
									} 
									if(!_atc.xol&&!_atc.xcs&&ac.ui_use_css!==false)
									{ 
										css.load(); 
										if(_7.bro.ie6||_7.bro.ie7)
										{ 
											_30a.load(); 
										} 
										if(_7.bro.ipa)
										{ 
											_30b.load(); 
										} 
									} 
							} 
							catch(e)
							{ 
								if(window.console)
								{ 
									console.log("main",e); 
								} 
							} 
							_87.bindReady(); 
							_87.append(main); 
						} 
						)(); 
						function addthis_open()
						{ 
							if(typeof iconf=="string")
							{ 
								iconf=null; 
							} 
							return _ate.ao.apply(_ate,arguments); 
						} 
						function addthis_close()
						{ 
							_ate.ac(); 
						} 
						function addthis_sendto()
						{ 
							_ate.as.apply(_ate,arguments); 
							return false; 
						} 
						if(_atc.dr)
						{ 
							_adr.onReady(); 
						} 
					} 
else
{ 
	_ate.inst++; 
} 
if(_atc.abf)
{ 
	addthis_open(document.getElementById("ab"),"emailab",window.addthis_url||"[URL]",window.addthis_title||"[TITLE]"); 
} 
if(!window.addthis.osta)
{ 
	addthis.osta=1; 
	window.addthis.ed=_ate.ed; 
	window.addthis.cache=
	{ 
	} 
	; 
	var s_list=
	{ 
a1webmarks:"A1&#8209; 
		   Webmarks",aim:"AOL Lifestream",amazonwishlist:"Amazon",aolmail:"AOL Mail",aviary:"Aviary Capture",domaintoolswhois:"Whois Lookup",googlebuzz:"Google Buzz",googlereader:"Google Reader",googletranslate:"Google Translate",linkagogo:"Link-a-Gogo",meneame:"Men&eacute; 
		   ame",misterwong:"Mister Wong",mailto:"Email App",myaol:"myAOL",myspace:"MySpace",readitlater:"Read It Later",rss:"RSS",stumbleupon:"StumbleUpon",typepad:"TypePad",wordpress:"WordPress",yahoobkm:"Y! Bookmarks",yahoomail:"Y! Mail",youtube:"YouTube"} 
			   ,d=document,postloaded=0; 
		   function getServiceName(a,b)
		   { 
			   var c; 
			   if(window._atw&&_atw.list&&_atw.list[a])
			   { 
				   c=_atw.list[a]} 
			   else
			   { 
				   if(s_list[a])
				   { 
					   c=s_list[a]} 
				   else
				   { 
					   c=(b?a:(a.substr(0,1).toUpperCase()+a.substr(1)))} 
			   } 
			   return(c||"").replace(/&nbsp; 
			   /g," ")} 
		   function gebcn(a,m,k,h,l)
		   { 
			   m=m.toUpperCase(); 
			   var j=document,f=(a==body&&addthis.cache[m]?addthis.cache[m]:(a||body||j.body).getElementsByTagName(m)),e=[],g,c; 
			   if(a==body)
			   { 
				   addthis.cache[m]=f} 
			   if(l)
			   { 
				   for(g=0; 
					   g<f.length; 
					   g++)
				   { 
					   c=f[g]; 
					   if((c.className||"").indexOf(k)>-1)
					   { 
						   e.push(c)} 
				   } 
			   } 
			   else
			   { 
				   k=k.replace(/\-/g,"\\-"); 
				   var b=new RegExp("\\b"+k+(h?"\\w*":"")+"\\b"); 
				   for(g=0; 
					   g<f.length; 
					   g++)
				   { 
					   c=f[g]; 
					   if(b.test(c.className))
					   { 
						   e.push(c)} 
				   } 
			   } 
			   return(e)} 
		   function nativeGetElementsByClassName(g,l,h)
		   { 
			   g=g||document; 
			   if(l=="*")
			   { 
				   l=null} 
			   var b=(document.getElementsByClassName?function(m,i)
			   { 
				   return m.getElementsByClassName(h)} 
			   :(document.querySelectorAll?function(m,i)
			   { 
				   return document.querySelectorAll(h)} 
			   :function()
			   { 
				   return[]} 
			   )),a=b(g,h),k=(l)?new RegExp("\\b"+l+"\\b","i"):null,c=[],f; 
			   for(var e=0,j=a.length; 
				   e<j; 
				   e+=1)
			   { 
				   f=a[e]; 
				   if(!k||k.test(f.nodeName))
				   { 
					   c.push(f)} 
			   } 
			   return c} 
		   var getElementsByClassName=((document.getElementsByClassName||document.querySelectorAll)&&!(document.documentMode==8))?nativeGetElementsByClassName:gebcn; 
		   function select(a)
		   { 
			   if(typeof a=="string")
			   { 
				   var b=a.substr(0,1); 
				   if(b=="#")
				   { 
					   a=document.getElementById(a.substr(1))} 
				   else
				   { 
					   if(b==".")
					   { 
						   a=getElementsByClassName(body,"*",a.substr(1))} 
					   else
					   { 
					   } 
				   } 
			   } 
			   if(!a)
			   { 
				   a=[]} 
			   else
			   { 
				   if(!(a instanceof Array))
				   { 
					   a=[a]} 
			   } 
			   return a} 
		   window.addthis.init=function()
		   { 
			   _adr.onReady(); 
			   addthis.ready&&addthis.ready()} 
		   ; 
		   window.addthis._select=select; 
		   window.addthis._gebcn=gebcn; 
		   window.addthis.getServiceName=getServiceName; 
		   window.addthis.util.getServiceName=getServiceName; 
		   window.addthis.addEventListener=_ate.util.bind(_ate.ed.addEventListener,_ate.ed); 
		   window.addthis.removeEventListener=_ate.util.bind(_ate.ed.removeEventListener,_ate.ed); 
		   _ate.extend(addthis,_ate.api); 
		   var d=document,u=undefined,w=window,subscribedTwitter=0,customServices=
		   { 
		   } 
		   ,top_services=
		   { 
more:1,compact:1,expanded:1,facebook:1,email:1,twitter:1,print:1,google:1,google_plusone_share:1,live:1,stumbleupon:1,vk:1,pinterest:1,myspace:1,favorites:1,digg:1,delicious:1,orkut:1,blogger:1,mailto:1,linkedin:1,mymailru:1,gmail:1,yahoomail:1,reddit:1,tumblr:1,live:1} 
			   ,top_services16=
			   { 
more:1,compact:1,expanded:1,"100zakladok":1,adifni:1,aim:1,amazonwishlist:1,arto:1,baidu:1,bitly:1,blip:1,blogger:1,bloggy:1,bobrdobr:1,delicious:1,digg:1,diggita:1,draugiem:1,ekudos:1,email:1,facebook:1,favorites:1,friendfeed:1,gmail:1,google:1,google_plusone_share:1,hatena:1,hotmail:1,hyves:1,igoogle:1,jappy:1,linkedin:1,live:1,livejournal:1,mailto:1,meinvz:1,meneame:1,misterwong:1,mymailru:1,myspace:1,netlog:1,nujij:1,oknotizie:1,oneview:1,orkut:1,oyyla:1,pinterest:1,plurk:1,print:1,pusha:1,reddit:1,sonico:1,studivz:1,stumbleupon:1,tuenti:1,tumblr:1,twitter:1,viadeo:1,vk:1,wordpress:1,wykop:1,xing:1,yahoobkm:1,yahoomail:1,yorumcuyum:1} 
				   ,css32=new _ate.resource.Resource("widget32css",_atc.rsrcs.widget32css,function()
				   { 
					   return true} 
				   ),need32=false,globalConfig,globalShare,upConfig=
				   { 
				   } 
				   ,upShare=
				   { 
				   } 
				   ,body=null,_select=addthis._select,buttons=[],f_title=
				   { 
rss:"Subscribe via RSS"} 
					   ,b_title=
					   { 
tweet:"Tweet",email:"Email",mailto:"Email",print:"Print",favorites:"Save to Favorites",twitter:"Tweet This",digg:"Digg This",more:"View more services"} 
						   ,json=
						   { 
email_vars:1,passthrough:1,modules:1,templates:1,services_custom:1} 
							   ,nosend=
							   { 
feed:1,more:_atc.ver<300,email:_atc.ver<300,mailto:1} 
								   ,nowindow=
								   { 
feed:1,email:_atc.ver<300,mailto:1,print:1,more:!_ate.bro.ipa&&_atc.ver<300,favorites:1} 
									   ,trackable=
									   { 
print:1,favorites:1,mailto:1} 
										   ,sharetowindow=
										   { 
email:_atc.ver>=300,more:_atc.ver>=300} 
											   ,renderGAttempts=0,renderTAttempts=0,renderDQAttempts=0,tryingToRenderGPO=0,tryingToRenderT=0; 
											   function unaccent(a)
											   { 
												   if(a.indexOf("&")>-1)
												   { 
													   a=a.replace(/&([aeiou]).+; 
													   /g,"$1")} 
												   return a} 
											   function mrg(b,c)
											   { 
												   if(c&&b!==c)
												   { 
													   for(var a in c)
													   { 
														   if(b[a]===u)
														   { 
															   b[a]=c[a]} 
													   } 
												   } 
											   } 
											   function addEvents(e,b,f)
											   { 
												   if(!e)
												   { 
													   return} 
												   var c=e.onclick||function()
												   { 
												   } 
												   ,a=trackable[b]?function()
												   { 
													   _ate.share.track(b,0,e.share,e.conf)} 
												   :function()
												   { 
													   _ate.share.notify(b,e.share,e.conf,e)} 
												   ; 
												   if(e.conf.data_ga_tracker||addthis_config.data_ga_tracker||e.conf.data_ga_property||addthis_config.data_ga_property)
												   { 
													   e.onclick=function()
													   { 
														   _ate.gat(b,f,e.conf,e.share); 
														   a(); 
														   return c()} 
												   } 
												   else
												   { 
													   e.onclick=function(g)
													   { 
														   a(); 
														   return c(g)} 
												   } 
											   } 
											   function getFollowUrl(c,b,a)
											   { 
												   var e=
												   { 
googlebuzz:"http://www.google.com/profiles/%s",google_follow:"https://plus.google.com/%s",youtube:"http://www.youtube.com/user/%s",facebook:"http://www.facebook.com/profile.php?id=%s",facebook_url:"http://www.facebook.com/%s",rss:"%s",flickr:"http://www.flickr.com/photos/%s",twitter:"http://twitter.com/intent/follow?source=followbutton&variant=1.0&screen_name=%s",linkedin:(a?(a=="group"?"http://www.linkedin.com/groups?gid=%s":"http://www.linkedin.com/company/%s"):"http://www.linkedin.com/in/%s"),vimeo:"http://www.vimeo.com/%s"} 
													   ; 
													   if(c=="facebook"&&isNaN(parseInt(b)))
													   { 
														   c="facebook_url"} 
													   return(e[c]||"").replace("%s",b)||""} 
											   function check32(b,a)
											   { 
												   if(need32&&!a)
												   { 
													   return true} 
												   var c=b.parentNode||
												   { 
												   } 
												   ; 
												   while(c.parentNode&&(c.className||"").search(/addthis_toolbox/i)<0)
												   { 
													   c=c.parentNode} 
												   need32=((c.className||"").search(/32x32/i)>-1||(b.className||"").search(/32x32/i)>-1); 
												   return need32} 
											   function registerProductCode(b)
											   { 
												   var c=(b.parentNode||
												   { 
												   } 
												   ).className||"",a=b.conf&&b.conf.product&&c.indexOf("toolbox")==-1?b.conf.product:"tbx"+(b.className.indexOf("32x32")>-1||c.indexOf("32x32")>-1?"32":"")+"-"+_atc.ver; 
												   if(a.indexOf(32)>-1)
												   { 
													   need32=true} 
												   _ate.track.apc(a); 
												   return a} 
											   function rpl(c,e)
											   { 
												   var b=
												   { 
												   } 
												   ; 
												   for(var a in c)
												   { 
													   if(e[a])
													   { 
														   b[a]=e[a]} 
													   else
													   { 
														   b[a]=c[a]} 
												   } 
												   return b} 
											   function _makeButton(a,e,f,c)
											   { 
												   var b=document.ce("img"); 
												   b.width=a; 
												   b.height=e; 
												   b.border=0; 
												   b.alt=f; 
												   b.src=c; 
												   return b} 
											   function _parseThirdPartyAttributes(e,f)
											   { 
												   var c,a=[],g=
												   { 
												   } 
												   ; 
												   for(var b=0; 
													   b<e.attributes.length; 
													   b++)
												   { 
													   c=e.attributes[b]; 
													   a=c.name.split(f+":"); 
													   if(a.length==2)
													   { 
														   g[a.pop()]=c.value} 
												   } 
												   return g} 
											   _ate.api.ptpa=_parseThirdPartyAttributes; 
											   function _parseAttributes(b,j,a,f)
											   { 
												   var j=j||
												   { 
												   } 
												   ,c=
												   { 
												   } 
												   ,h=_parseThirdPartyAttributes(b,"addthis"); 
												   for(var g in j)
												   { 
													   c[g]=j[g]} 
												   if(f)
												   { 
													   for(var g in b[a])
													   { 
														   c[g]=b[a][g]} 
												   } 
												   for(var g in h)
												   { 
													   if(j[g]&&!f)
													   { 
														   c[g]=j[g]} 
													   else
													   { 
														   var l=h[g]; 
														   if(l)
														   { 
															   c[g]=l} 
														   else
														   { 
															   if(j[g])
															   { 
																   c[g]=j[g]} 
														   } 
														   if(c[g]==="true")
														   { 
															   c[g]=true} 
														   else
														   { 
															   if(c[g]==="false")
															   { 
																   c[g]=false} 
														   } 
													   } 
													   if(c[g]!==u&&json[g]&&(typeof c[g]=="string"))
													   { 
														   try
														   { 
															   c[g]=JSON.parse(c[g].replace(/'/g,'"'))} 
																   catch(i)
															   { 
																   c[g]=_ate.evl("("+c[g]+"); 
																	   ",true)} 
															   } 
														   } 
														   return c} 
													   function _processCustomServices(c)
													   { 
														   var b=(c||
														   { 
														   } 
														   ).services_custom; 
														   if(!b)
														   { 
															   return} 
														   if(!(b instanceof Array))
														   { 
															   b=[b]} 
														   for(var e=0; 
															   e<b.length; 
															   e++)
														   { 
															   var a=b[e]; 
															   if(a.name&&a.icon&&a.url)
															   { 
																   if(typeof a.url=="object")
																   { 
																	   a.url=_ate.util.toKV(a.url)} 
																   a.code=a.url=a.url.replace(/ /g,""); 
																   a.code=a.code.split("//").pop().split("?").shift().split("/").shift().toLowerCase(); 
																   customServices[a.code]=a} 
														   } 
													   } 
													   function _getCustomService(b,a)
													   { 
														   return customServices[b]||
														   { 
														   } 
													   } 
													   function _getATtributes(b,a,c,e)
													   { 
														   var f=
														   { 
conf:a||
	 { 
	 } 
	 ,share:c||
	 { 
	 } 
														   } 
														   ; 
														   f.conf=_parseAttributes(b,a,"conf",e); 
														   f.share=_parseAttributes(b,c,"share",e); 
														   return f} 
													   function _render(A,j,r,g)
													   { 
														   _ate.igv(); 
														   if(A)
														   { 
															   j=j||
															   { 
															   } 
															   ; 
															   r=r||
															   { 
															   } 
															   ; 
															   var B=j.conf||globalConfig,y=j.share||globalShare,f=r.onmouseover,c=r.onmouseout,D=r.onclick,m=r.internal,n=undefined,t=r.singleservice; 
															   if(t)
															   { 
																   if(D===n)
																   { 
																	   D=nosend[t]?function(E,i,F)
																	   { 
																		   var o=rpl(F,upShare); 
																		   return addthis_open(E,t,o.url,o.title,rpl(i,upConfig),o)} 
																	   :nowindow[t]?function(E,i,F)
																	   { 
																		   var o=rpl(F,upShare); 
																		   return addthis_sendto(t,rpl(i,upConfig),o)} 
																	   :sharetowindow[t]?function(E,i,F)
																	   { 
																		   var o=rpl(F,upShare); 
																		   return _ate.share.stw(t,o,i,735)} 
																	   :null} 
															   } 
															   else
															   { 
																   if(!r.noevents)
																   { 
																	   if(!r.nohover)
																	   { 
																		   if(f===n)
																		   { 
																			   f=function(o,i,E)
																			   { 
																				   return addthis_open(o,"",null,null,rpl(i,upConfig),rpl(E,upShare))} 
																		   } 
																		   if(c===n)
																		   { 
																			   c=function(i)
																			   { 
																				   return addthis_close()} 
																		   } 
																		   if(D===n)
																		   { 
																			   D=function(o,i,E)
																			   { 
																				   return addthis_sendto("more",rpl(i,upConfig),rpl(E,upShare))} 
																		   } 
																	   } 
																	   else
																	   { 
																		   if(D===n)
																		   { 
																			   D=function(o,i,E)
																			   { 
																				   return addthis_open(o,"more",null,null,rpl(i,upConfig),rpl(E,upShare))} 
																		   } 
																	   } 
																   } 
															   } 
															   A=_select(A); 
															   for(var z=0; 
																   z<A.length; 
																   z++)
															   { 
																   var q=A[z],v=q.parentNode,b=_getATtributes(q,B,y,!g)||
																   { 
																   } 
																   ; 
																   mrg(b.conf,globalConfig); 
																   mrg(b.share,globalShare); 
																   q.conf=b.conf; 
																   q.share=b.share; 
																   if(q.conf.ui_language)
																   { 
																	   _ate.alg(q.conf.ui_language)} 
																   _processCustomServices(q.conf); 
																   if(v&&v.className.indexOf("toolbox")>-1&&(q.conf.product||"").indexOf("men")===0)
																   { 
																	   q.conf.product="tbx"+(v.className.indexOf("32x32")>-1?"32":"")+"-"+_atc.ver; 
																	   _ate.track.apc(q.conf.product)} 
																   if(t&&t!=="more")
																   { 
																	   q.conf.product=registerProductCode(q)} 
																   if((!q.conf||(!q.conf.ui_click&&!q.conf.ui_window_panes))&&!_ate.bro.ipa)
																   { 
																	   _ate.maf=_ate.maf||
																	   { 
																	   } 
																	   ; 
																	   _ate.maf.home=this; 
																	   _ate.maf.key=null; 
																	   _ate.maf.shift=null; 
																	   if(f)
																	   { 
																		   q.onfocus=q.onmouseover=function()
																		   { 
																			   _ate.maf.sib=this.nextSibling; 
																			   while(_ate.maf.sib&&_ate.maf.sib.nodeType==3&&_ate.maf.sib.nextSibling)
																			   { 
																				   _ate.maf.sib=_ate.maf.sib.nextSibling} 
																			   if(!_ate.maf.sib||_ate.maf.sib.nodeType==3)
																			   { 
																				   var i=this.parentNode; 
																				   if(!i)
																				   { 
																					   i=document.body.firstChild||document.body; 
																					   while(i.nodeType==3&&i.nextSibling)
																					   { 
																						   i=i.nextSibling} 
																				   } 
																				   else
																				   { 
																					   while(i.nextSibling&&i.nodeType==3)
																					   { 
																						   i=i.nextSibling} 
																				   } 
																				   _ate.maf.sib=i} 
																			   _ate.maf.sib.onfocus=function()
																			   { 
																				   _ate.maf.sib.tabIndex=""} 
																			   ; 
																			   return f(this,this.conf,this.share)} 
																	   } 
																	   if(c)
																	   { 
																		   q.onmouseout=function()
																		   { 
																			   return c(this)} 
																	   } 
																	   if(D)
																	   { 
																		   q.onclick=function()
																		   { 
																			   return D(q,q.conf,q.share)} 
																	   } 
																	   if(c||D)
																	   { 
																		   q.onkeypress=q.onkeydown=function(i)
																		   { 
																			   if(!i)
																			   { 
																				   var i=window.event} 
																			   if(i.shiftKey)
																			   { 
																				   _ate.maf.shift=true} 
																			   if(i.keyCode)
																			   { 
																				   _ate.maf.key=i.keyCode} 
																			   else
																			   { 
																				   if(i.which)
																				   { 
																					   _ate.maf.key=i.which} 
																			   } 
																			   if(_ate.maf.key==13)
																			   { 
																				   _ate.maf.pre=this} 
																			   else
																			   { 
																				   _ate.maf.pre=null} 
																		   } 
																		   ; 
																		   q.onblur=function(i)
																		   { 
																			   if(_ate.maf.key==9&&_ate.maf.firstCompact&&!_ate.maf.shift&&this.className.indexOf("compact")>-1)
																			   { 
																				   _ate.maf.key=null; 
																				   _ate.maf.acm=true; 
																				   document.getElementById(_ate.maf.firstCompact).focus()} 
																			   else
																			   { 
																				   _ate.maf.key=null; 
																				   _ate.maf.shift=null; 
																				   if(c)
																				   { 
																					   return c(this)} 
																			   } 
																		   } 
																	   } 
																   } 
																   else
																   { 
																	   if(D)
																	   { 
																		   if(t)
																		   { 
																			   q.onclick=function()
																			   { 
																				   return D(this,this.conf,this.share)} 
																		   } 
																		   else
																		   { 
																			   if(!q.conf.ui_window_panes)
																			   { 
																				   q.onclick=function()
																				   { 
																					   if(_ate.bro.iph||_ate.bro.dro)
																					   { 
																						   return addthis_sendto("more",this.conf,this.share)} 
																					   else
																					   { 
																						   return addthis_open(this,"",null,null,this.conf,this.share)} 
																				   } 
																			   } 
																			   else
																			   { 
																				   q.onclick=function()
																				   { 
																					   return addthis_sendto("more",this.conf,this.share)} 
																			   } 
																		   } 
																	   } 
																   } 
																   if(q.tagName.toLowerCase()=="a")
																   { 
																	   var e=q.share.url||addthis_share.url; 
																	   _ate.usu(e); 
																	   if(t)
																	   { 
																		   var l=_getCustomService(t,q.conf),a=q.firstChild; 
																		   if(l&&l.code&&l.icon)
																		   { 
																			   if(a&&a.className.indexOf("at300bs")>-1)
																			   { 
																				   var p="16"; 
																				   if(check32(q,1))
																				   { 
																					   a.className=a.className.split("at15nc").join(""); 
																					   p="32"} 
																				   a.style.background="url("+l.icon+") no-repeat top left transparent"; 
																				   if(!a.style.cssText)
																				   { 
																					   a.style.cssText=""} 
																				   a.style.cssText="line-height:"+p+"px!important; 
width:"+p+"px!important; 
height:"+p+"px!important; 
background:"+a.style.background+"!important"} 
																			   } 
																			   if(!nowindow[t])
																			   { 
																				   if(r.follow)
																				   { 
																					   q.href=e; 
																					   q.conf=(q.conf||
{ 
																						   } 
																						   ); 
																						   q.conf.follow=true; 
																						   q.onclick=function()
{ 
																							   _ate.share.track(t,1,q.share,q.conf); 
																							   if(t=="twitter")
{ 
																								   _ate.share.ocw(q.href,"520px","520px"); 
																								   return false} 
																						   } 
																						   ; 
																						   if(q.children&&q.children.length==1&&q.parentNode&&q.parentNode.className.indexOf("toolbox")>-1)
{ 
																							   var x=document.ce("span"); 
																							   x.className="addthis_follow_label"; 
																							   x.innerHTML=t=="google_follow"?"Google":addthis.util.getServiceName(t).replace("_follow",""); 
																							   q.appendChild(x)} 
																					   } 
																					   else
{ 
																						   if(t=="twitter")
{ 
																							   q.onclick=function(i)
{ 
																								   return _ate.share.pts(q.share,q.conf)} 
																							   ; 
																							   q.noh=1} 
																						   else
{ 
																							   if(t=="facebook")
{ 
																								   q.onclick=function(i)
{ 
																									   return _ate.share.fb.share(q.share,q.conf)} 
																								   ; 
																								   q.noh=1} 
																							   else
{ 
																								   if(t=="google_plusone")
{ 
																									   q.onclick=function(i)
{ 
																										   return false} 
																								   } 
																								   else
{ 
																									   if(t=="foursquare")
{ 
																										   q.onclick=function(i)
{ 
																											   _ate.share.track(t,1,q.share,q.conf); 
																											   return false} 
																									   } 
																									   else
{ 
																										   if(t=="link")
{ 
																											   q.onclick=function(o)
{ 
																												   var i=_euc(q.share.url); 
																												   if(_atc.ver>=300)
{ 
																													   _ate.share.ocw(_atc.rsrcs.link+"#url="+_euc(i)+"&ats="+_euc(_ate.util.rtoKV(q.share))+"&atc="+_euc(_ate.util.rtoKV(q.config)),"500px","480px")} 
																												   else
{ 
																													   addthis_open(document.body,"link",i); 
																													   if(document.getElementById("at16p"))
{ 
																														   document.getElementById("at16p").style.display="block"} 
																													   if(document.getElementById("at15s"))
{ 
																														   document.getElementById("at15s").style.display="none"} 
																												   } 
																												   return false} 
																										   } 
																										   else
{ 
																											   if(!q.noh)
{ 
																												   if(q.conf.ui_open_windows||_ate.share.auw(t))
{ 
																													   q.onclick=function(i)
{ 
																														   return _ate.share.stw(t,q.share,q.conf)} 
																												   } 
																												   else
{ 
																													   q.onclick=function(i)
{ 
																														   return _ate.share.siw(t,q.share,q.conf)} 
																													   ; 
																													   q.href=_ate.share.genurl(t,0,q.share,q.conf)} 
																											   } 
																										   } 
																									   } 
																								   } 
																							   } 
																						   } 
																					   } 
																					   addEvents(q,t,e); 
																					   if(!q.noh&&!q.target)
{ 
																						   q.target="_blank"} 
																					   addthis.links.push(q)} 
																				   else
{ 
																					   if(t=="mailto"||(t=="email"&&(q.conf.ui_use_mailto||_ate.bro.iph||_ate.bro.ipa||_ate.bro.dro)))
{ 
																						   q.onclick=function()
{ 
																							   q.share.xid=_ate.util.cuid(); 
																							   (new Image()).src=_ate.share.genurl("mailto",0,q.share,q.config); 
																							   _ate.gat(t,e,q.conf,q.share)} 
																						   ; 
																						   q.href=_ate.share.genieu(q.share,q.config||q.conf); 
																						   addthis.ems.push(q)} 
																				   } 
																				   if(!q.title||q.at_titled)
{ 
																					   var k=addthis.util.getServiceName(t,!l); 
																					   q.title=unaccent(r.follow?(f_title[t]?f_title[t]:"Follow on "+k):(b_title[t]?b_title[t]:"Send to "+k)); 
																					   q.at_titled=1} 
																				   if(!q.href)
{ 
																					   q.href="#"} 
																			   } 
																			   else
{ 
																				   if(q.conf.product&&q.parentNode.className.indexOf("toolbox")==-1)
{ 
																					   registerProductCode(q)} 
																			   } 
																		   } 
																		   var h; 
																		   switch(m)
{ 
																		   case"img":if(!q.hasChildNodes())
{ 
																			   var C=(q.conf.ui_language||_ate.lng()).split("-").shift(),s=_ate.ivl(C); 
																			   if(!s)
{ 
																				   C="en"} 
																			   else
{ 
																				   if(s!==1)
{ 
																					   C=s} 
																			   } 
																			   h=_makeButton(_ate.iwb(C)?150:125,16,"Share",_atr+"static/btn/v2/lg-share-"+C.substr(0,2)+".gif")} 
																					 break} 
																		   if(h)
{ 
																			   q.appendChild(h)} 
																	   } 
															   } 
														   } 
														   function renderPlusOne()
{ 
															   if(window.gapi&&window.gapi.plusone)
{ 
																   gapi.plusone.go(); 
																   return} 
															   else
{ 
																   if(!tryingToRenderGPO)
{ 
																	   var a=_ate.ajs("//apis.google.com/js/plusone.js",1,1); 
																	   tryingToRenderGPO=1} 
															   } 
															   if(renderGAttempts<3)
{ 
																   setTimeout(renderPlusOne,3000+1000*2*(renderGAttempts++))} 
														   } 
														   function addGoogleSubscriptions(a)
{ 
															   var c=a?a.share:addthis_share,b=a?a.conf:addthis_config; 
															   window._at_plusonecallback=window._at_plusonecallback||function(g)
{ 
																   var e=
{ 
																   } 
																   ; 
																   for(var f in c)
{ 
																	   e[f]=c[f]} 
																   e.url=g.href; 
																   _ate.share.track("google_"+(g.state=="off"?"un":"")+"plusone",0,e,b)} 
														   } 
														   function addDisqusSubscriptions(a)
{ 
															   var e=a?a.share:addthis_share,c=a?a.conf:addthis_config; 
															   if(window.DISQUS)
{ 
																   var b=function(h)
{ 
																	   var f=_ate.util.clone(addthis_share); 
																	   for(var g in h)
{ 
																		   f[g]=h[g]} 
																	   if(typeof f.url==="undefined")
{ 
																		   f.url=window.location.href} 
																	   _ate.share.track("disqus_comment",0,f,c)} 
																   ; 
																   DISQUS.reset(
{ 
reload:true,config:function()
{ 
																	   this.callbacks.onNewComment=[function(f)
{ 
																		   b(f)} 
																	   ]} 
																   } 
																   )} 
															   else
{ 
																   if(renderDQAttempts<5)
{ 
																	   setTimeout(addDisqusSubscriptions,100*(renderDQAttempts++))} 
															   } 
														   } 
														   function addTwitterSubscriptions()
{ 
															   if(window.twttr&&!subscribedTwitter&&twttr.events)
{ 
																   subscribedTwitter=1; 
																   twttr.events.bind("click",function(g)
{ 
																	   if(g.region=="tweetcount")
{ 
																		   return} 
																	   var f=(g.target.parentNode&&g.target.parentNode.share)?g.target.parentNode.share:
{ 
																	   } 
																	   ,c=f.url||g.target.baseURI,h=f.title||addthis_share.title,a=
{ 
																	   } 
																	   ; 
																	   for(var b in addthis_share)
{ 
																		   a[b]=addthis_share[b]} 
																	   for(var b in f)
{ 
																		   a[b]=f[b]} 
																	   a.url=c; 
																	   if(h)
{ 
																		   a.title=h} 
																	   var e=(g.region!="follow")?true:false; 
																	   _ate.share.track(((e)?"tweet":"twitter_follow_native"),((e)?0:1),a,addthis_config)} 
																   )} 
														   } 
														   function renderTweet(a)
{ 
															   if(window.twttr&&window.twttr.events&&tryingToRenderT==1)
{ 
																   addTwitterSubscriptions(); 
																   tryingToRenderT=renderTAttempts=0; 
																   return} 
															   else
{ 
																   if(!tryingToRenderT)
{ 
																	   _ate.ajs("//platform.twitter.com/widgets.js",1,null,null,null,true); 
																	   tryingToRenderT=1} 
															   } 
															   if(renderTAttempts<3)
{ 
																   setTimeout(renderTweet,3000+1000*2*(renderTAttempts++))} 
														   } 
														   function _renderToolbox(aw,an,aQ,ar,aK)
{ 
															   for(var T=0; 
																   T<aw.length; 
																   T++)
{ 
																	   var aa=aw[T],X=document; 
																	   if(aa==null)
{ 
																		   continue} 
																	   if(ar!==false||!aa.ost)
{ 
																		   var W=_getATtributes(aa,an,aQ,!aK),am=0,ab="at300",Y=aa.className||"",l="",L=Y.match(/addthis_button_([\w\.]+)(?:\s|$)/),ah=
{ 
																		   } 
																		   ,av=L&&L.length?L[1]:0; 
																		   mrg(W.conf,globalConfig); 
																		   mrg(W.share,globalShare); 
																		   if(av)
{ 
																			   if(av.indexOf("amazonwishlist_native")>-1)
{ 
																			   } 
																			   else
{ 
																				   if(av==="link")
{ 
																					   if(_ate.bro.ie9&&_atc.ver<300)
{ 
																						   continue} 
																					   aa.title="Permalink"} 
																				   else
{ 
																					   if(av==="tweetmeme"&&aa.className.indexOf("chiclet_style")==-1)
{ 
																						   if(aa.ost)
{ 
																							   continue} 
																						   var aD=_parseThirdPartyAttributes(aa,"tm"),h=50,n=61; 
																						   l=_ate.util.toKV(aD); 
																						   if(aD.style==="compact")
{ 
																							   h=95; 
																							   n=25} 
																						   aa.innerHTML='<iframe frameborder="0" width="'+h+'" height="'+n+'" scrolling="no" allowTransparency="true" scrollbars="no"'+(_ate.bro.ie6?" src=\"javascript:''\"":"")+"></iframe>"; 
																						   var aj=aa.firstChild; 
																						   aj.src="//api.tweetmeme.com/button.js?url="+_euc(W.share.url)+"&"+l; 
																						   aa.noh=aa.ost=1} 
																					   else
{ 
																						   if(av==="google_plusone")
{ 
																							   if(aa.ost)
{ 
																								   continue} 
																							   var aq=_parseThirdPartyAttributes(aa,"g:plusone"),ae=document.ce("g:plusone"),aM=""; 
																							   _ate.gpl=_ate.gpl||
{ 
																							   } 
																							   ,_ate.gpl.lang=_ate.gpl.lang||null; 
																							   aq.lang=_ate.gpl.lang=_ate.gpl.lang||((typeof aq.lang=="undefined")?null:aq.lang); 
																							   window.___gcfg=window.___gcfg||
{ 
																							   } 
																							   ; 
																							   window.___gcfg.lang=_ate.gpl.lang||aq.lang||_ate.ggl((W.conf||
{ 
																							   } 
																							   ).ui_language||window.addthis_language)||"en-US"; 
																							   aq.href=aq.href||_ate.track.mgu(W.share.url,
{ 
defrag:1} 
																								   ); 
																								   aq.size=aq.size||(check32(aa,true)?"standard":"small"); 
																								   aq.callback=aq.callback||"_at_plusonecallback"; 
																								   addGoogleSubscriptions(W); 
																								   for(var R in aq)
{ 
																									   if(aq.hasOwnProperty(R))
{ 
																										   ae.setAttribute(R,aq[R])} 
																								   } 
																								   aa.appendChild(ae); 
																								   aa.noh=aa.ost=1; 
																								   renderPlusOne()} 
																						   else
{ 
																							   if(av==="google_plusone_badge")
{ 
																								   if(aa.ost)
{ 
																									   continue} 
																								   aa.title="Follow on Google+"; 
																								   var af=_parseThirdPartyAttributes(aa,"g:plusone"); 
																								   af.size=(af.size||"").toLowerCase(); 
																								   if(document.head)
{ 
																									   var m=document.createElement("link"); 
																									   m.setAttribute("href",af.href); 
																									   m.setAttribute("rel","publisher"); 
																									   document.head.appendChild(m)} 
																								   af.url=af.href=af.href||""; 
																								   if(af.size=="badge"||af.size=="smallbadge")
{ 
																									   var ay=document.ce("g:plus"),aJ=""; 
																									   _ate.gpl=_ate.gpl||
{ 
																									   } 
																									   ,_ate.gpl.lang=_ate.gpl.lang||null; 
																									   af.lang=_ate.gpl.lang=_ate.gpl.lang||((typeof af.lang=="undefined")?null:af.lang); 
																									   window.___gcfg=window.___gcfg||
{ 
																									   } 
																									   ; 
																									   window.___gcfg.lang=_ate.gpl.lang||af.lang||_ate.ggl((W.conf||
{ 
																									   } 
																									   ).ui_language||window.addthis_language)||"en-US"; 
																									   for(var R in af)
{ 
																										   if(af.hasOwnProperty(R))
{ 
																											   ay.setAttribute(R,af[R])} 
																									   } 
																									   aa.appendChild(ay); 
																									   aa.noh=aa.ost=1; 
																									   renderPlusOne()} 
																								   else
{ 
																									   var K="32"; 
																									   if(af.size=="small")
{ 
																										   K="16"} 
																									   else
{ 
																										   if(af.size=="large")
{ 
																											   K="64"} 
																									   } 
																									   var ad=txt=txt2=ieQ=""; 
																									   if(af.name)
{ 
																										   if(_ate.bro.compatMode=="BackCompat"&&_ate.bro.msi)
{ 
																											   ieQ='onclick="window.open('+af.href+'?prsrc=3)"'} 
																										   ad="cursor:default; 
display:inline-block; 
																										   text-decoration:none; 
color:#333; 
font:13px/16px arial,sans-serif; 
																										   "+((af.size=="large")?"text-align:center; 
																										   white-space:nowrap; 
																										   ":""); 
																											   if(af.size=="large")
{ 
																												   txt2='<br/><span style="font-weight:bold; 
																													   ">'+af.name+"</span><br/><span> on Google+ </span>"} 
																											   else
{ 
																												   txt='<span style="display:inline-block; 
																													   font-weight:bold; 
																												   vertical-align:top; 
																												   margin-right:5px; 
																												   '+((af.size=="medium")?"margin-top:8px; 
																													   ":"")+'">'+af.name+'</span><span style="display:inline-block; 
																													   vertical-align:top; 
																												   margin-right:'+((af.size=="medium")?"15px; 
																													   margin-top:8px; 
																												   ":"13px; 
																												   ")+'">on</span>'} 
																												   } 
																												   aa.setAttribute("target","_blank"); 
																												   aa.style.textDecoration="none"; 
																												   aa.style.cursor="default"; 
																												   aa.innerHTML='<span style="'+ad+'">'+txt+"<img "+ieQ+' src="https://ssl.gstatic.com/images/icons/gplus-'+K+'.png" alt="'+aa.title+'" style="border:0; 
width:'+K+"px; 
height:"+K+'px; 
cursor:pointer; 
																												   " onmouseover="this.style.opacity=0.8; 
																												   this.style.filter=\'alpha(opacity=80)\'; 
																													   " onmouseout="this.style.opacity=1.0; 
																												   this.style.filter=\'alpha(opacity=100)\'; 
																													   ">'+txt2+"</span>"; 
																													   aa.noh=aa.ost=1; 
																												   aa.onclick=function(a)
{ 
																													   if(!a)
{ 
																														   var a=window.event} 
																													   var c=a.originalTarget||a.relatedTarget||a.toElement||a.srcElement,b=""; 
																													   if(!c)
{ 
																														   return} 
																													   while(c.nodeName!="A")
{ 
																														   c=c.parentNode} 
																													   b=((c.attributes||
{ 
																													   } 
																													   )["g:plusone:href"]||
{ 
																													   } 
																													   ).value||window.location.href; 
																													   w.open(b+"?prsrc=3"); 
																													   _ate.share.track("google_plusone_badge",1,af,an); 
																													   return false} 
																											   } 
																											   aa.onmouseover=function()
{ 
																												   this.className=(this.className.indexOf("at300bo")>-1)?this.className:this.className.replace(/at300b/i,"at300bo")} 
																											   ; 
																											   aa.noh=aa.ost=1} 
																									   else
{ 
																										   if(av==="pinterest"||av==="pinterest_count"||av==="pinterest_pinit")
{ 
																											   if(aa.ost)
{ 
																												   continue} 
																											   var aR=_parseThirdPartyAttributes(aa,"pi:pinit"),r=_ate.util.clone(W.share); 
																											   aR.url=r.url=aR.url||_ate.track.mgu(r.url,
{ 
defrag:1} 
																												   ); 
																												   aR.url=r.url=_euc(_ate.share.acb("pinterest",r,addthis_config)); 
																												   if(_ate.bro.ie6||_ate.bro.ie7||(_ate.bro.msi&&document.compatMode=="BackCompat"))
{ 
																													   aR.layout=""} 
																												   if(aR.layout=="horizontal")
{ 
																													   aR.layout="&layout=horizontal"; 
																													   aR.width="110px"; 
																													   aR.height="26px"} 
																												   else
{ 
																													   if(aR.layout=="vertical")
{ 
																														   aR.layout="&layout=vertical"; 
																														   aR.width="49px"; 
																														   aR.height="59px"} 
																													   else
{ 
																														   aR.layout=""; 
																														   aR.width="49px"; 
																														   aR.height="26px"} 
																												   } 
																												   aa.innerHTML='<iframe frameborder="0" role="presentation" scrolling="no" allowTransparency="true" scrollbars="no"'+(_ate.bro.ie6?" src=\"javascript:''\"":"")+' style="width:'+aR.width+"; 
height:"+aR.height+'; 
	   "></iframe>'; 
	   pinitButton=aa.firstChild; 
																												   if(!W.conf.pubid)
{ 
																													   W.conf.pubid=addthis_config.pubid||_ate.pub()} 
																												   pinitButton.src=_atc.rsrcs.pinit+"?url="+_euc(aR.url)+"&media="+_euc(aR.media||"")+aR.layout+"&ats="+_euc(_ate.util.rtoKV(r))+"&atc="+_euc(_ate.util.rtoKV(addthis_config)); 
																												   aa.noh=aa.ost=1} 
																										   else
{ 
																											   if(av==="foursquare")
{ 
																												   if(aa.ost)
{ 
																													   continue} 
																												   var aS=_parseThirdPartyAttributes(aa,"4sq"),ax=document.createElement("a"); 
																												   ax.href="https://foursquare.com/intent/venue.html"; 
																												   ax.className="fourSq-widget"; 
																												   if(aS["data-variant"])
{ 
																													   ax.setAttribute("data-variant",aS["data-variant"])} 
																												   aa.appendChild(ax); 
																												   _ate.ajs("//platform.foursquare.com/js/widgets.js",1); 
																												   aa.noh=aa.ost=1} 
																											   else
{ 
																												   if(av==="linkedin_counter")
{ 
																													   if(aa.ost)
{ 
																														   continue} 
																													   var ap=_parseThirdPartyAttributes(aa,"li"),aQ=W.share,aN=ap.width||100,f=ap.height||18,l,y="",ag; 
																													   if(!ap.counter)
{ 
																														   ap.counter="horizontal"} 
																													   if(!aQ.passthrough)
{ 
																														   aQ.passthrough=
{ 
																														   } 
																													   } 
																													   aQ.passthrough.linkedin=_ate.util.toKV(ap); 
																													   y=_ate.util.rtoKV(aQ); 
																													   if(ap.counter==="top")
{ 
																														   f=55; 
																														   aN=57; 
																														   if(!ap.height)
{ 
																															   ap.height=f} 
																														   if(!ap.width)
{ 
																															   ap.width=aN} 
																													   } 
																													   else
{ 
																														   if(ap.counter==="right")
{ 
																															   aN=100; 
																															   if(!ap.width)
{ 
																																   ap.width=M} 
																														   } 
																													   } 
																													   if(ap.width)
{ 
																														   aN=ap.width} 
																													   if(ap.height)
{ 
																														   f=ap.height} 
																													   l=_ate.util.toKV(ap),aa.innerHTML='<iframe frameborder="0" role="presentation" scrolling="no" allowTransparency="true" scrollbars="no"'+(_ate.bro.ie6?" src=\"javascript:''\"":"")+' style="width:'+aN+"px; 
height:"+f+'px; 
	   "></iframe>'; 
	   ag=aa.firstChild; 
																													   if(!W.conf.pubid)
{ 
																														   W.conf.pubid=addthis_config.pubid||_ate.pub()} 
																													   ag.src=_atc.rsrcs.linkedin+((_ate.bro.ie6||_ate.bro.ie7)?"?":"#")+"href="+_euc(W.share.url)+"&dr="+_euc(_ate.dr)+"&conf="+_euc(_ate.util.toKV(W.conf))+"&share="+_euc(y)+"&li="+_euc(l); 
																													   aa.noh=aa.ost=1} 
																												   else
{ 
																													   if(av==="twitter_follow_native")
{ 
																														   var aB=_parseThirdPartyAttributes(aa,"tf"),P=_parseThirdPartyAttributes(aa,"tw"),S=document.ce("a"); 
																														   aB.screen_name=P.screen_name||aB.screen_name||"addthis"; 
																														   S.href="http://twitter.com/"+aB.screen_name; 
																														   S.className="twitter-follow-button"; 
																														   S.innerHTML="Follow @"+aB.screen_name; 
																														   for(var aA in aB)
{ 
																															   if(aB.hasOwnProperty(aA))
{ 
																																   S.setAttribute("data-"+aA,aB[aA])} 
																														   } 
																														   for(var aA in P)
{ 
																															   if(P.hasOwnProperty(aA))
{ 
																																   S.setAttribute("data-"+aA,P[aA])} 
																														   } 
																														   aa.appendChild(S); 
																														   if(!W.conf.pubid)
{ 
																															   W.conf.pubid=addthis_config.pubid||_ate.pub()} 
																														   renderTweet(aa)} 
																													   else
{ 
																														   if(av==="tweet")
{ 
																															   if(aa.ost)
{ 
																																   continue} 
																															   var P=_parseThirdPartyAttributes(aa,"tw"),aQ=W.share,M=P.width||55,ac=P.height||20,l,y="",ao; 
																															   W.share.url_transforms=W.share.url_transforms||
{ 
																															   } 
																															   ; 
																															   W.share.url_transforms.defrag=1; 
																															   var aE=_ate.util.clone(W.share),aI=((_ate.bro.msi&&X.compatMode=="BackCompat")||W.conf.ui_use_tweet_iframe||(W.share.url_transforms.shorten||
{ 
																															   } 
																															   ).twitter=="bitly")?true:false; 
																															   if(typeof P.url!="undefined")
{ 
																																   aE.url=P.url} 
																															   else
{ 
																																   aE.url=P.url=_ate.track.mgu((aE.url||(addthis_share||
{ 
																																   } 
																																   ).url),aE.url_transforms,aE,"twitter")} 
																															   if(!P.counturl)
{ 
																																   P.counturl=(aI)?P.url.replace(/=/g,"%253D"):P.url} 
																															   if(aE.url.search(/\.+.*(\/|\?)/)==-1)
{ 
																																   aE.url+="/"} 
																															   P.url=_ate.share.acb("twitter",aE,addthis_config); 
																															   P.count=P.count||"horizontal"; 
																															   aQ.passthrough=aQ.passthrough||
{ 
																															   } 
																															   ; 
																															   var al=aQ.passthrough.twitter||
{ 
																															   } 
																															   ; 
																															   W.text=P.text=P.text||((W.share.title==X.title)?al.text:W.share.title)||""; 
																															   W.related=P.related=P.related||al.related||""; 
																															   W.via=P.via=P.via||al.via||(W.text.match(/via\s+@[a-zA-Z0-9_\.]+/i)?W.text.match(/via\s+@[a-zA-Z0-9_\.]+/i).split("@")[1]:"AddThis"); 
																															   y=_ate.util.rtoKV(aQ,"#@!"); 
																															   if(P.count==="vertical")
{ 
																																   ac=62; 
																																   P.height=P.height||ac} 
																															   else
{ 
																																   if(P.count==="horizontal")
{ 
																																	   M=110; 
																																	   P.width=P.width||M} 
																															   } 
																															   if(P.width)
{ 
																																   M=P.width} 
																															   if(P.height)
{ 
																																   ac=P.height} 
																															   l=_ate.util.toKV(P,"#@!"); 
																															   if(aI)
{ 
																																   aa.innerHTML='<iframe frameborder="0" role="presentation" scrolling="no" allowTransparency="true" scrollbars="no"'+(_ate.bro.ie6?" src=\"javascript:''\"":"")+' style="width:'+M+"px; 
height:"+ac+'px; 
	   "></iframe>'; 
	   ao=aa.firstChild; 
																																   if(!W.conf.pubid)
{ 
																																	   W.conf.pubid=addthis_config.pubid||_ate.pub()} 
																																   ao.src=_atc.rsrcs.tweet+((_ate.bro.ie6||_ate.bro.ie7)?"?":"#")+"href="+_euc(P.url)+"&dr="+_euc(_ate.dr)+"&conf="+_euc(_ate.util.toKV(W.conf))+"&share="+_euc(y)+"&tw="+_euc(l)} 
																															   else
{ 
																																   var O=(aQ.templates||
{ 
																																   } 
																																   ).twitter||""; 
																																   if(!P.text)
{ 
																																	   P.text=aQ.title==""?"":aQ.title+":"} 
																																   var t=X.ce("a"); 
																																   t.href="http://twitter.com/share"; 
																																   t.className="twitter-share-button"; 
																																   t.innerHTML="Tweet"; 
																																   for(var aA in P)
{ 
																																	   if(P.hasOwnProperty(aA))
{ 
																																		   t.setAttribute("data-"+aA,P[aA])} 
																																   } 
																																   aa.appendChild(t); 
																																   if(!W.conf.pubid)
{ 
																																	   W.conf.pubid=addthis_config.pubid||_ate.pub()} 
																																   renderTweet(aa)} 
																															   aa.noh=aa.ost=1} 
																														   else
{ 
																															   if(av==="facebook_send")
{ 
																																   if(aa.ost||_ate.bro.ie6)
{ 
																																	   continue} 
																																   var aH,au=_parseThirdPartyAttributes(aa,"fb:send"),N="",B=au.width||55,H=au.height||20; 
																																   l=_ate.util.toKV(au); 
																																   _ate.ufbl=1; 
																																   if(_ate.share.fb.ready())
{ 
																																	   au.href=au.href||_ate.track.mgu(W.share.url,
{ 
defrag:1} 
																																		   ); 
																																		   for(var R in au)
{ 
																																			   N+=" "+R+'="'+au[R]+'"'} 
																																		   aa.innerHTML='<fb:send ref="'+_ate.share.gcp(W.share,W.conf,".send").replace(",","_")+'" '+N+"></fb:send>"; 
																																		   _ate.share.fb.load(aa)} 
																																   else
{ 
																																	   aa.className=""; 
																																	   aa.innerHTML="<span></span>"; 
																																	   aa.style.width=aa.style.height="0px"} 
																																   aa.noh=aa.ost=1} 
																															   else
{ 
																																   if(av==="facebook_share")
{ 
																																	   W.conf=W.conf||
{ 
																																	   } 
																																	   ; 
																																	   W.conf.data_track_clickback=W.conf.data_track_linkback=false; 
																																	   function E(b,a)
{ 
																																		   if(!b)
{ 
																																			   return} 
																																		   b.setAttribute("style",a); 
																																		   b.style.cssText=a; 
																																		   return} 
																																	   var Q="AT"+_ate.util.cuid(),au=_parseThirdPartyAttributes(aa,"fb:share"),G=X.ce("span"),aL=X.ce("div"),g=X.ce("div"),ak=X.ce("div"),V=X.ce("div"),aO=X.ce("div"),A=W.share.url=au.href||_ate.track.mgu(W.share.url,
{ 
defrag:1} 
																																		   ),e=typeof(e)!="undefined"?e:
{ 
																																		   } 
																																		   ; 
																																		   e[Q]=A.replace(/\#.*/,""); 
																																		   E(G,"text-decoration:none; 
color:#000000; 
display:inline-block; 
cursor:pointer; 
																																		   "); 
																																			   E(ak,"text-decoration:none; 
																																			   margin-top:10px; 
																																		   "); 
																																			   E(g,"display:block; 
																																			   z-index:-1; 
background:none repeat scroll 0 0 #ECEEF5; 
border:1px solid #CAD4E7; 
filter:none; 
																																		   border-radius: 4px; 
color:#000000; 
																																		   font-family:Verdana,Helvetica,sans-serif; 
																																		   font-size:18px; 
																																		   line-height:16px; 
height:39px; 
																																		   text-align:center; 
width:58px; 
																																		   "); 
																																			   E(V,"display:block; 
margin:-1px 0 0px 10px; 
height:4px; 
width:10px; 
																																		   font-size:1px; 
																																		   line-height:4px; 
background:url('"+_atr+"static/t00/fb_arrow.png') no-repeat ; 
																																		   "); 
																																			   E(aO,"background-image:url('"+_atr+"static/t00/fb_btn.png'); 
																																			   background-repeat:no-repeat; 
display:inline-block; 
																																		   font-family:Verdana,Helvetica,sans-serif; 
																																		   font-size:1px; 
height:22px; 
																																		   line-height:16px; 
																																		   white-space:nowrap; 
width:60px; 
																																		   "); 
																																			   ak.innerHTML="0"; 
																																		   ak.id=Q; 
																																		   V.innerHTML="&nbsp; 
																																			   "; 
																																			   W.share.passthrough=W.share.passthrough||
{ 
																																		   } 
																																		   ; 
																																		   W.share.passthrough.facebook_share=_ate.util.toKV(
{ 
src:"sp"} 
																																			   ); 
																																			   aO.onmouseover=function()
{ 
																																				   this.style.opacity="0.75"} 
																																			   ; 
																																			   aO.onmouseout=function()
{ 
																																				   this.style.opacity="1.0"} 
																																			   ; 
																																			   aO.onclick=function()
{ 
																																				   var a=this.parentNode.firstChild.firstChild; 
																																				   if(a&&isNaN(a.innerHTML)!=true)
{ 
																																					   var b=parseInt(a.innerHTML)+1; 
																																					   a.removeChild(a.firstChild); 
																																					   a.appendChild(document.createTextNode(b))} 
																																			   } 
																																			   ; 
																																			   g.appendChild(ak); 
																																			   aL.appendChild(g); 
																																			   aL.appendChild(V); 
																																			   aL.appendChild(aO); 
																																			   G.appendChild(aL); 
																																			   aa.appendChild(G); 
																																			   aa.style.textDecoration="none"; 
																																			   var U=_ate.util.scb("fbsc",A,function(c)
{ 
																																				   if(c.length>0)
{ 
																																					   for(var a in e)
{ 
																																						   if(e[a]==c[0].url)
{ 
																																							   var k=c[0].share_count,b=document.getElementById(a); 
																																							   if(k>10000)
{ 
																																								   k=parseInt(k/1000)+"K"} 
																																							   if(b.firstChild)
{ 
																																								   b.removeChild(b.firstChild)} 
																																							   b.appendChild(document.createTextNode(k))} 
																																					   } 
																																				   } 
																																			   } 
																																			   ,function()
{ 
																																			   } 
																																			   ); 
																																			   _ate.ajs("//api.facebook.com/restserver.php?method=links.getStats&format=json&callback="+U+"&urls="+A,1)} 
																																   else
{ 
																																	   if(av==="facebook_like")
{ 
																																		   _ate.share.fb.like(aa,W)} 
																																	   else
{ 
																																		   if(av==="facebook_subscribe")
{ 
																																			   _ate.share.fb.subs(aa,W)} 
																																		   else
{ 
																																			   if(av.indexOf("stumbleupon_badge")>-1)
{ 
																																				   if(_ate.bro.ie6)
{ 
																																					   continue} 
																																				   var x=_parseThirdPartyAttributes(aa,"su:badge"),j=x.style||"1",at=W.share.url=x.href||_ate.track.mgu(W.share.url,
{ 
defrag:1} 
																																					   ),aC=x.height||"20px",J=x.width||"75px"; 
																																					   if(j=="5")
{ 
																																						   aC=x.height||"60px"} 
																																					   else
{ 
																																						   if(j=="6")
{ 
																																							   aC=x.height||"31px"} 
																																					   } 
																																					   aa.innerHTML='<iframe src="http'+(_ate.ssl?"s":"")+'://www.stumbleupon.com/badge/embed/
{ 
																																					   
{ 
																																						   STYLE} 
																																			   } 
																																			   /?url=
{ 
																																				   
{ 
																																					   URL} 
																																			   } 
																																			   " scrolling="no" frameborder="0" style="border:none; 
overflow:hidden; 
width:
{ 
		  
{ 
			  WIDTH} 
	  } 
	  ; 
height:
{ 
		   
{ 
			   HEIGHT} 
	   } 
	   ; 
	   " allowtransparency="true"></iframe>'.replace("
{ 
		   
{ 
			   STYLE} 
	   } 
	   ",j).replace("
{ 
		   
{ 
			   URL} 
	   } 
	   ",_euc(at)).replace("
{ 
		   
{ 
			   HEIGHT} 
	   } 
	   ",aC).replace("
{ 
		   
{ 
			   WIDTH} 
	   } 
	   ",J); 
		   aa.noh=aa.ost=1} 
																								   else
{ 
																									   if(av.indexOf("hyves_respect")>-1)
{ 
																										   var aG=_parseThirdPartyAttributes(aa,"hy:respect"),p=W.share.url=aG.url||_ate.track.mgu(W.share.url,
{ 
defrag:1} 
																											   ),ai=aG.width||"140px",Z='<iframe src="http'+(_ate.ssl?"s":"")+'://www.hyves.nl/respect/button?url=
{ 
																											   
{ 
																												   URL} 
																									   } 
																									   " style="border: medium none; 
overflow:hidden; 
width:
{ 
		  
{ 
			  WIDTH} 
	  } 
	  ; 
height:22px; 
	  " scrolling="no" frameborder="0" allowTransparency="true" ></iframe>'.replace("
{ 
		  
{ 
			  URL} 
	  } 
	  ",_ate.share.acb("hyves",W.share,addthis_config)).replace("
{ 
		  
{ 
			  WIDTH} 
	  } 
	  ",ai); 
		  aa.innerHTML=Z; 
	  aa.noh=aa.ost=1} 
																								   else
{ 
																									   if(av.indexOf("preferred")>-1)
{ 
																										   if(aa._iss)
{ 
																											   continue} 
																										   L=Y.match(/addthis_button_preferred_([0-9]+)(?:\s|$)/); 
																										   var z=((L&&L.length)?Math.min(16,Math.max(1,parseInt(L[1]))):1)-1; 
																										   if(!aa.conf)
{ 
																											   aa.conf=
{ 
																											   } 
																										   } 
																										   aa.conf.product="tbx-"+_atc.ver; 
																										   registerProductCode(aa); 
																										   if(window._atw)
{ 
																											   if(!aa.parentNode.services)
{ 
																												   aa.parentNode.services=
{ 
																												   } 
																											   } 
																											   var v=_atw.conf.services_exclude||"",F=_atw.loc,aF=aa.parentNode.services,aP=_ate.util.unqconcat(addthis_options.replace(",more","").split(","),F.split(",")); 
																											   do
{ 
																												   av=aP[z++]} 
																											   while(z<aP.length&&(v.indexOf(av)>-1||aF[av])||(_ate.bro.ie9&&av=="link")); 
																											   if(aF[av])
{ 
																												   for(var R in _atw.list)
{ 
																													   if(!aF[R]&&v.indexOf(R)==-1)
{ 
																														   av=R; 
																														   break} 
																												   } 
																											   } 
																											   aa._ips=1; 
																											   if(aa.className.indexOf(av)==-1)
{ 
																												   aa.className+=" addthis_button_"+av; 
																												   aa._iss=1} 
																											   aa.parentNode.services[av]=1} 
																										   else
{ 
																											   _ate.alg(W.conf.ui_language||window.addthis_language); 
																											   _ate.plo.unshift(["deco",_renderToolbox,[aa],an,aQ,true]); 
																											   if(_ate.gssh)
{ 
																												   _ate.pld=_ate.ajs(_atc.rsrcs.menujs)} 
																											   else
{ 
																												   if(!_ate.pld)
{ 
																													   _ate.pld=1; 
																													   var o=function()
{ 
																														   _ate.pld=_ate.ajs(_atc.rsrcs.menujs)} 
																													   ; 
																													   if(_ate.upm)
{ 
																														   _ate._rec.push(function(a)
{ 
																															   if(a.ssh)
{ 
																																   o()} 
																														   } 
																														   ); 
																														   setTimeout(o,500)} 
																													   else
{ 
																														   o()} 
																												   } 
																											   } 
																											   continue} 
																									   } 
																									   else
{ 
																										   if(av.indexOf("follow")>-1)
{ 
																											   if(av=="google_follow")
{ 
																												   aa.title="Follow on Google"} 
																											   else
{ 
																												   av=av.split("_follow").shift()} 
																											   ah.follow=true; 
																											   W.share.url=getFollowUrl(av,W.share.userid,W.share.usertype)} 
																									   } 
																								   } 
																																	   } 
																																   } 
																															   } 
																														   } 
																													   } 
																												   } 
																											   } 
																										   } 
																									   } 
																								   } 
																							   } 
																						   } 
																					   } 
																				   } 
																			   } 
																			   if(_ate.bro.msi&&!document.getElementById("at300bhoveriefilter"))
{ 
																				   var C=document.getElementsByTagName("head")[0],ad=document.createElement("style"),q=document.createTextNode(".at300b:hover,.at300bs:hover 
{ 
filter:alpha(opacity=80); 
																			   } 
																			   "); 
																				   ad.id="at300bhoveriefilter"; 
																			   ad.type="text/css"; 
																			   if(ad.styleSheet)
{ 
																				   ad.styleSheet.cssText=q.nodeValue} 
																			   else
{ 
																				   ad.appendChild(q)} 
																			   C.appendChild(ad)} 
																		   if(!top_services[av]&&(need32||check32(aa)))
{ 
																			   css32.load()} 
																		   var D=(top_services16[av]&&!check32(aa)); 
																		   if(!aa.childNodes.length)
{ 
																			   var az=X.ce("span"); 
																			   aa.appendChild(az); 
																			   az.className=(D?"at16nc ":" ")+ab+"bs at15nc at15t_"+av+(D?" at16t_"+av:""); 
																			   if(az!=undefined&&(av==="compact"||av==="expanded"))
{ 
																				   az.innerHTML='<span class="at_a11y">More Sharing Services</span>'} 
																			   else
{ 
																				   if(az!=undefined)
{ 
																					   az.innerHTML='<span class="at_a11y">Share on '+av+"</span>"} 
																			   } 
																		   } 
																		   else
{ 
																			   if(aa.childNodes.length==1)
{ 
																				   var I=aa.childNodes[0]; 
																				   if(I.nodeType==3)
{ 
																					   var az=X.ce("span"); 
																					   aa.insertBefore(az,I); 
																					   az.className=(D?"at16nc ":" ")+ab+"bs at15nc at15t_"+av+(D?" at16t_"+av:"")} 
																				   if(az!=undefined&&(av==="compact"||av==="expanded"))
{ 
																					   az.innerHTML='<span class="at_a11y">More Sharing Services</span>'} 
																				   else
{ 
																					   if(az!=undefined)
{ 
																						   az.innerHTML='<span class="at_a11y">Share on '+av+"</span>"} 
																				   } 
																			   } 
																			   else
{ 
																				   if(aa.firstChild&&aa.firstChild.nodeType==3&&aa.firstChild.textContent=="\n")
{ 
																				   } 
																				   else
{ 
																					   am=1} 
																			   } 
																		   } 
																		   if(av==="compact"||av==="expanded")
{ 
																			   if(!am&&Y.indexOf(ab)==-1)
{ 
																				   aa.className+=" "+ab+"m"} 
																			   if(W.conf.product&&W.conf.product.indexOf("men-")==-1)
{ 
																				   W.conf.product+=",men-"+_atc.ver} 
																			   if(!aa.href)
{ 
																				   aa.href="#"} 
																			   if(aa.parentNode&&aa.parentNode.services)
{ 
																				   W.conf.parentServices=aa.parentNode.services} 
																			   if(av==="expanded")
{ 
																				   ah.nohover=true; 
																				   ah.singleservice="more"} 
																		   } 
																		   else
{ 
																			   if((aa.parentNode.className||"").indexOf("toolbox")>-1)
{ 
																				   if(!aa.parentNode.services)
{ 
																					   aa.parentNode.services=
{ 
																					   } 
																				   } 
																				   aa.parentNode.services[av]=1} 
																			   if(!am&&Y.indexOf(ab)==-1)
{ 
																				   aa.className+=" "+ab+"b"} 
																			   ah.singleservice=av} 
																		   if(aa._ips)
{ 
																			   ah.issh=true} 
																		   _render([aa],W,ah,aK); 
																		   aa.ost=1; 
																		   registerProductCode(aa)} 
															   } 
														   } 
													   } 
													   function gat(l,a,i,k)
{ 
														   if(l=="facebook_unlike"||l=="google_unplusone")
{ 
															   return} 
														   i=i||
{ 
														   } 
														   ; 
														   var c=i.data_ga_tracker,g=i.data_ga_property; 
														   if(g)
{ 
															   if(typeof(window._gat)=="object"&&_gat._getTracker)
{ 
																   c=_gat._getTracker(g)} 
															   else
{ 
																   if(typeof(window._gaq)=="object"&&_gaq._getAsyncTracker)
{ 
																	   c=_gaq._getAsyncTracker(g)} 
																   else
{ 
																	   if(typeof(window._gaq)=="array")
{ 
																		   _gaq.push([function()
{ 
																			   _ate.gat(l,a,i,k)} 
																		   ])} 
																   } 
															   } 
														   } 
														   if(c&&typeof(c)=="string")
{ 
															   c=window[c]} 
														   if(c&&typeof(c)=="object")
{ 
															   if(l=="more"||l=="settings")
{ 
																   return} 
															   var j=a||(k||
{ 
															   } 
															   ).url||location.href,b=l,f="share"; 
															   if(b.indexOf("_")>-1)
{ 
																   b=b.split("_"); 
																   f=b.pop(); 
																   if(f.length<=2)
{ 
																	   f="share"} 
																   b=b.shift()} 
															   if(j.toLowerCase().replace("https","http").indexOf("http%3a%2f%2f")==0)
{ 
																   j=_duc(j)} 
															   try
{ 
																   if(i.data_ga_social&&c._trackSocial&&l!="google_plusone")
{ 
																	   c._trackSocial(b,f,k.url)} 
																   else
{ 
																	   c._trackEvent("addthis",l,j)} 
															   } 
															   catch(h)
{ 
																   try
{ 
																	   c._initData(); 
																	   if(i.data_ga_social&&c._trackSocial&&l!="google_plusone")
{ 
																		   c._trackSocial(b,f,k.url)} 
																	   else
{ 
																		   c._trackEvent("addthis",l,j)} 
																   } 
																   catch(h)
{ 
																   } 
															   } 
														   } 
													   } 
													   _ate.gat=gat; 
													   addthis.update=function(h,f,c)
{ 
														   if(h=="share")
{ 
															   if(f=="url")
{ 
																   _ate.usu(0,1)} 
															   if(!window.addthis_share)
{ 
																   window.addthis_share=
{ 
																   } 
															   } 
															   window.addthis_share[f]=c; 
															   upShare[f]=c; 
															   for(var a in addthis.links)
{ 
																   var g=addthis.links[a],e=new RegExp("&"+f+"=(.*)&"),b="&"+f+"="+_euc(c)+"&"; 
																   if((g.conf||
{ 
																   } 
																   ).follow)
{ 
																	   continue} 
																   if(g.share)
{ 
																	   g.share[f]=c} 
																   if(!g.noh)
{ 
																	   g.href=g.href.replace(e,b); 
																	   if(g.href.indexOf(f)==-1)
{ 
																		   g.href+=b} 
																   } 
															   } 
															   for(var a in addthis.ems)
{ 
																   var g=addthis.ems[a]; 
																   g.href=_ate.share.genieu(addthis_share)} 
														   } 
														   else
{ 
															   if(h=="config")
{ 
																   if(!window.addthis_config)
{ 
																	   window.addthis_config=
{ 
																	   } 
																   } 
																   window.addthis_config[f]=c; 
																   upConfig[f]=c} 
														   } 
													   } 
													   ; 
													   addthis._render=_render; 
													   var counterResources=[new _ate.resource.Resource("countercss",_atc.rsrcs.countercss,function()
{ 
														   return true} 
													   ),new _ate.resource.Resource("counter",_atc.rsrcs.counter,function()
{ 
														   return window.addthis.counter.ost} 
													   )]; 
													   if(_ate.bro.ie6||_ate.bro.ie7)
{ 
														   counterResources.push(new _ate.resource.Resource("counterIE67css",_atc.rsrcs.counterIE67css,function()
{ 
															   return true} 
														   ))} 
													   if(!w.JSON||!w.JSON.stringify)
{ 
														   counterResources.unshift(new _ate.resource.Resource("json2",_atr+"static/r07/json2.js",function()
{ 
															   return w.JSON&&w.JSON.stringify} 
														   ))} 
													   addthis.counter=function(e,b,c)
{ 
														   var f=counterResources; 
														   if(e)
{ 
															   e=addthis._select(e); 
															   if(e.length)
{ 
																   if(!addthis.counter.selects)
{ 
																	   addthis.counter.selects=[]} 
																   addthis.counter.selects=addthis.counter.selects.concat(
{ 
counter:e,config:b,share:c} 
																	   ); 
																	   for(var a in f)
{ 
																		   if((f[a]||
{ 
																		   } 
																		   ).load)
{ 
																			   f[a].load()} 
																	   } 
															   } 
														   } 
													   } 
													   ; 
													   addthis.count=function(e,b,c)
{ 
														   var f=counterResources; 
														   if(e)
{ 
															   e=addthis._select(e); 
															   if(e.length)
{ 
																   if(!addthis.count.selects)
{ 
																	   addthis.count.selects=[]} 
																   addthis.count.selects=addthis.count.selects.concat(
{ 
counter:e,config:b,share:c} 
																	   ); 
																	   for(var a in f)
{ 
																		   if((f[a]||
{ 
																		   } 
																		   ).load)
{ 
																			   f[a].load()} 
																	   } 
															   } 
														   } 
													   } 
													   ; 
													   addthis.data.getShareCount=function(e,b)
{ 
														   var c=counterResources; 
														   if(!addthis.counter.reqs)
{ 
															   addthis.counter.reqs=[]} 
														   addthis.counter.reqs.push(
{ 
share:b,callback:e} 
															   ); 
															   for(var a in c)
{ 
																   if((c[a]||
{ 
																   } 
																   ).load)
{ 
																	   c[a].load()} 
															   } 
													   } 
													   ; 
													   var barResources=[new _ate.resource.Resource("barjs",_atc.rsrcs.barjs,function()
{ 
														   return true} 
													   )]; 
													   if(document.compatMode=="BackCompat"&&_ate.bro.msi&&false)
{ 
														   barResources.push(new _ate.resource.Resource("barcss",_atc.rsrcs.qbarcss,function()
{ 
															   return true} 
														   ))} 
													   else
{ 
														   barResources.push(new _ate.resource.Resource("barcss",_atc.rsrcs.barcss,function()
{ 
															   return true} 
														   ))} 
													   addthis.bar=function(j,c,g,a)
{ 
														   if(j)
{ 
															   j=addthis._select(j); 
															   if(j.length)
{ 
																   if(!addthis.bar.selects)
{ 
																	   addthis.bar.selects=[]} 
																   addthis.bar.selects=addthis.bar.selects.concat(j); 
																   for(var e=0; 
																	   e<j.length; 
																	   e++)
{ 
																		   var f=j[e],h="bar"+(f.className.indexOf("vertical")>-1?"vt":"hz")+"-"+_atc.ver; 
																		   _ate.track.apc(h)} 
																   for(var b in barResources)
{ 
																	   if((barResources[b]||
{ 
																	   } 
																	   ).load)
{ 
																		   barResources[b].load()} 
																   } 
															   } 
														   } 
													   } 
													   ; 
													   var overlayResources=new _ate.resource.Resource("overlayjs",_atc.rsrcs.overlayjs,function()
{ 
														   return true} 
													   ); 
													   addthis.overlay=function(e,b,c,a)
{ 
														   if(e)
{ 
															   e=addthis._select(e); 
															   if(e.length)
{ 
																   if(!addthis.overlay.selects)
{ 
																	   addthis.overlay.selects=[]} 
																   addthis.overlay.selects=addthis.overlay.selects.concat(e); 
																   _ate.track.apc("ovr-"+_atc.ver); 
																   if((overlayResources||
{ 
																   } 
																   ).load)
{ 
																	   overlayResources.load()} 
															   } 
														   } 
													   } 
													   ; 
													   addthis.button=function(c,a,b)
{ 
														   a=a||
{ 
														   } 
														   ; 
														   if(!a.product)
{ 
															   a.product="men-"+_atc.ver} 
														   _render(c,
{ 
conf:a,share:b} 
															   ,
{ 
internal:"img"} 
															   )} 
													   ; 
													   addthis.toolbox=function(j,b,k,l)
{ 
														   var m=_select(j); 
														   for(var f=0; 
															   f<m.length; 
															   f++)
{ 
																   var e=m[f],g=_getATtributes(e,b,k,l),a=document.ce("div"),h; 
																   e.services=
{ 
																   } 
																   ; 
																   if(!g.conf.product)
{ 
																	   g.conf.product="tbx"+(e.className.indexOf("32x32")>-1?"32":"")+"-"+_atc.ver} 
																   if(e)
{ 
																	   h=e.getElementsByTagName("a"); 
																	   if(h)
{ 
																		   _renderToolbox(h,g.conf,g.share,!l,!l)} 
																	   e.appendChild(a)} 
																   a.className="atclear"} 
													   } 
													   ; 
													   function validateServiceCode(a)
{ 
														   if(!a||a.length<5||a.length>30)
{ 
															   throw new Error("Service code must be between 5 and 30 characters.")} 
														   else
{ 
															   if(a.search(/^[a-zA-Z0-9_]+$/)==-1)
{ 
																   throw new Error("Service code must consist entirely of letters, numbers and underscores.")} 
														   } 
														   return true} 
													   addthis.logShare=function(e,a,h,b)
{ 
														   var i=b||addthis_config,g=h||addthis_share; 
														   i.product="hdl-"+_atc.ver; 
														   g.imp_url=0; 
														   var e=e||(h&&h.url)||addthis_share.url,f=_ate.track.dcu(e); 
														   if(f.rsc&&!a)
{ 
															   a=f.rsc} 
														   if(validateServiceCode(a))
{ 
															   g.url=e; 
															   _ate.share.track(a,0,g,i)} 
													   } 
													   ; 
													   addthis.addClickTag=function(c,a,e,b)
{ 
														   var c=c||e&&e.url||addthis_share.url; 
														   if(validateServiceCode(a))
{ 
															   c=_ate.track.cur(_ate.track.cof(c),a)} 
														   return c} 
													   ; 
													   addthis.ready=function(a)
{ 
														   if(addthis.ost)
{ 
															   return} 
														   addthis.ost=1; 
														   doRenderPass(); 
														   _ate.ed.fire("addthis.ready",addthis); 
														   if(_ate.onr)
{ 
															   _ate.onr(addthis)} 
														   callPostLoads(); 
														   _ate.share.fb.sub(); 
														   addTwitterSubscriptions(); 
														   addGoogleSubscriptions(); 
														   if(typeof addthis_config.data_track_disqus!=="undefined")
{ 
															   addDisqusSubscriptions()} 
														   if(a&&typeof a=="function")
{ 
															   a()} 
													   } 
													   ; 
													   addthis.util.getAttributes=_getATtributes; 
													   addthis.ad=_ate.ad; 
													   function doRenderPass()
{ 
														   var b=addthis,c=".addthis_"; 
														   if(b.osrp)
{ 
															   return} 
														   b.osrp=1; 
														   globalShare=w.addthis_share; 
														   globalConfig=w.addthis_config; 
														   body=document.gn("body").item(0); 
														   buttons=addthis._gebcn(body,"A","addthis_button_",true,true); 
														   addthis.toolbox(c+"toolbox",null,null,true); 
														   addthis.button(c+"button"); 
														   addthis.counter(c+"counter"); 
														   addthis.count(c+"count"); 
														   addthis.bar(c+"bar"); 
														   addthis.overlay(c+"shareable"); 
														   _renderToolbox(buttons,null,null,false)} 
													   addEventListeners(); 
													   if(_atc.xol)
{ 
														   callPostLoads(); 
														   if(_adr.isReady)
{ 
															   doRenderPass()} 
													   } 
													   else
{ 
														   _adr.append((function()
{ 
															   window.addthis.ready()} 
														   ))} 
													   _ate.ed.fire("addthis-internal.ready",addthis)} 
												   function callPostLoads()
{ 
													   if(postloaded)
{ 
														   return} 
													   var a=window.addthis; 
													   for(var b=0,e=a.plo,c; 
														   b<e.length; 
														   b++)
{ 
															   c=e[b]; 
															   if(!c.called)
{ 
																   (c.ns?(typeof c.ns=="string"?a[c.ns]:c.ns):a)[c.call].apply(c.ctx?(typeof(c.ctx=="string")?a[c.ctx]:c.ctx):this,c.args)} 
													   } 
													   postloaded=1} 
												   function addEventListeners()
{ 
													   if(postloaded)
{ 
														   return} 
													   var a=window.addthis; 
													   for(var b=0,e=a.plo,c; 
														   b<e.length; 
														   b++)
{ 
															   c=e[b]; 
															   if(c.call=="addEventListener")
{ 
																   (c.ns?(typeof c.ns=="string"?a[c.ns]:c.ns):a)[c.call].apply(c.ctx?(typeof(c.ctx=="string")?a[c.ctx]:c.ctx):this,c.args); 
																   c.called=1} 
													   } 
												   } 
												   if(!window.addthis)
{ 
													   window.addthis=
{ 
													   } 
												   } 
												   addthis.user=(function()
{ 
													   var I=_ate,y=addthis,n=1000,r=
{ 
													   } 
													   ,l=0,f=0,k=0,j=
{ 
													   } 
													   ,p; 
													   addthis.HIGH=3; 
													   addthis.MED=2; 
													   addthis.LOW=1; 
													   addthis.ASC=1; 
													   addthis.DSC=addthis.DESC=0; 
													   function E(a,K)
{ 
														   return I.reduce(["getID","getGeolocation","getServiceShareHistory"],a,K)} 
													   function s(a,K)
{ 
														   return function(L)
{ 
															   setTimeout(function()
{ 
																   L(I[a]||K)} 
															   ,0)} 
													   } 
													   function A(a)
{ 
														   if(l)
{ 
															   return} 
														   if(!a||!a.uid)
{ 
															   return} 
														   if(p!==null)
{ 
															   clearTimeout(p)} 
														   p=null; 
														   l=1; 
														   E(function(M,K,L)
{ 
															   r[K]=r[K].queuer.flush(s.apply(y,M[L]),y); 
															   return M} 
														   ,[["uid",""],["geo",""],["_ssh",[]]])} 
													   function h()
{ 
														   if(!_ate.pld)
{ 
															   _ate.pld=(new _ate.resource.Resource("menujs",_atr+_atc.rsrcs.menujs,function()
{ 
																   return true} 
															   )).load()} 
													   } 
													   function e(a)
{ 
														   if(f&&(a.uid||a.ssh!==undefined))
{ 
															   h(); 
															   f=0} 
													   } 
													   function F()
{ 
														   var a=
{ 
uid:"x",geo:
{ 
	} 
	,ssh:"",ups:""} 
														   ; 
														   k=1; 
														   A(a); 
														   e(a)} 
													   p=setTimeout(F,n); 
													   I._rec.push(A); 
													   function g(L)
{ 
														   var K=
{ 
														   } 
														   ; 
														   for(var a=0; 
															   a<L.length; 
															   a++)
{ 
																   K[L[a]]=L[a]} 
														   return K} 
													   function H(L,M)
{ 
														   if(typeof(M)=="array")
{ 
															   M=g(M)} 
														   L=L.split(","); 
														   for(var K=0; 
															   K<L.length; 
															   K++)
{ 
																   var a=L[K].replace(/ /g,""); 
																   if(M[a])
{ 
																	   return 1} 
														   } 
														   return 0} 
													   function x(N,O,M)
{ 
														   if(typeof(O)=="array")
{ 
															   return 0} 
														   N=N.split(","); 
														   for(var L=0; 
															   L<N.length; 
															   L++)
{ 
																   var a=N[L].replace(/ /g,""); 
																   for(var K=0; 
																	   K<M.length; 
																	   M++)
{ 
																		   if(O[M[K]]==a)
{ 
																			   return 1} 
																   } 
														   } 
														   return 0} 
													   function i(a)
{ 
														   return I.util.geo.isin(a,I.geo)} 
													   function o(a)
{ 
														   return H(a,j.interests)} 
													   function q(a)
{ 
														   if(!_ate.uud)
{ 
															   _ate.ed.fire("addthis-internal.api",window.addthis||
{ 
															   } 
															   ,
{ 
call:"rdy"} 
																   )} 
														   _ate.uud=1; 
														   if(window._atw)
{ 
															   _atw.gps(function()
{ 
																   if(c())
{ 
																	   a(j); 
																	   return} 
																   j.interests=[]; 
																   for(var L in _ate.bti)
{ 
																	   j.interests.push(_ate.bti[L])} 
																   var O=[],K=
{ 
																   } 
																   ; 
																   if(I._uss)
{ 
																	   for(var N=0; 
																		   N<I._uss.length; 
																		   N++)
{ 
																			   if(!K[I._uss[N]])
{ 
																				   O.push(
{ 
name:I._uss[N],score:addthis.HIGH} 
																					   )} 
																	   } 
																   } 
																   if(I._ups)
{ 
																	   for(var N=0; 
																		   N<I._ups.length; 
																		   N++)
{ 
																			   if(!K[I._ups[N]])
{ 
																				   O.push(
{ 
name:I._ups[N],score:addthis.HIGH} 
																					   )} 
																	   } 
																   } 
																   if(I._ssc)
{ 
																	   for(var M in I._ssc)
{ 
																		   if(!K[M])
{ 
																			   O.push(
{ 
name:M,score:I._ssc[M]} 
																				   )} 
																	   } 
																   } 
																   j.services=O; 
																   j.activity=
{ 
																   } 
																   ; 
																   j.activity.social=_ate.bts; 
																   j.activity.view=_ate.vts; 
																   j.source=z(); 
																   if(_ate.geo&&typeof(_ate.geo)=="object"&&_ate.geo[0]&&_ate.geo[1])
{ 
																	   var P=""; 
																	   for(var N in _ate.geo)
{ 
																		   if(typeof(_ate.geo[N])=="string")
{ 
																			   P+=_ate.geo[N]} 
																	   } 
																	   _ate.geo=_ate.util.geo.parse(P)} 
																   for(var L in _ate.geo)
{ 
																	   if(!isNaN(parseInt(_ate.geo[L])))
{ 
																		   _ate.geo[L]=parseInt(_ate.geo[L])} 
																   } 
																   t.location=j.location=_ate.geo||
{ 
																   } 
																   ; 
																   j.location.contains=i; 
																   if(a)
{ 
																	   a(j)} 
																   _ate.ed.fire("addthis.user.data",window.addthis||
{ 
																   } 
																   ,
{ 
																   } 
																   )} 
															   )} 
														   else
{ 
															   _ate.ed.addEventListener("addthis.menu.ready",function()
{ 
																   q(a)} 
															   ); 
															   _ate.alg(); 
															   if(I.gssh||k)
{ 
																   h()} 
															   else
{ 
																   if(!I.pld&&!f)
{ 
																	   _ate._rec.push(e)} 
															   } 
															   f=1} 
													   } 
													   function m(a)
{ 
														   q(a)} 
													   r.getData=m; 
													   r.getPreferredServices=function(a)
{ 
														   if(window._atw)
{ 
															   _atw.gps(a)} 
														   else
{ 
															   _ate.ed.addEventListener("addthis.menu.ready",function()
{ 
																   _atw.gps(a)} 
															   ); 
															   _ate.alg(); 
															   if(I.gssh||k)
															   { 
																   h()} 
															   else
															   { 
																   if(!I.pld&&!f)
																   { 
																	   _ate._rec.push(e)} 
															   } 
															   f=1} 
													   } 
													   ; 
													   function c()
													   { 
														   _ate.ed.fire("addthis-internal.api",window.addthis||
														   { 
														   } 
														   ,
														   { 
call:"ioo"} 
															   ); 
															   return I.uid=="0000000000000000"} 
													   function D(a)
													   { 
														   _ate.ed.fire("addthis-internal.api",window.addthis||
														   { 
														   } 
														   ,
														   { 
call:"iuf"} 
															   ); 
															   return(I._ssh&&I._ssh.indexOf(a)>-1)||(I._ssc&&I._ssc[a])} 
													   function C(a)
													   { 
														   if(!a)
														   { 
															   a=[]} 
														   a._sortasc=function(K)
														   { 
															   a.sort(function(M,L)
															   { 
																   return a._isort(M,L,addthis.ASC,K)} 
															   )} 
														   ; 
														   a._sortdsc=function(K)
														   { 
															   a.sort(function(M,L)
															   { 
																   return a._isort(M,L,addthis.DSC,K)} 
															   )} 
														   ; 
														   a._isort=function(M,K,O,P)
														   { 
															   var N=M[P],L=K[P]; 
															   if(typeof(N)=="string"&&!isNaN(parseInt(N)))
															   { 
																   N=parseInt(N,10); 
																   L=parseInt(L,10); 
																   if(O)
																   { 
																	   return N-N} 
																   return N-L} 
															   if(N>L)
															   { 
																   return O?1:-1} 
															   else
															   { 
																   if(N==L)
																   { 
																	   return 0} 
															   } 
															   return O?-1:1} 
														   ; 
														   a.map=function(L)
														   { 
															   if(!L)
															   { 
																   L="name"} 
															   var M=
															   { 
															   } 
															   ; 
															   for(var K=0; 
																   K<a.length; 
																   K++)
															   { 
																   M[a[K][L]]=a[K]} 
															   return M} 
														   ; 
														   a.keys=function(M,L,N)
														   { 
															   if(!L)
															   { 
																   L="name"} 
															   if(!N)
															   { 
																   N="score"} 
															   var O=[]; 
															   if(M==addthis.ASC)
															   { 
																   a._sortasc(N)} 
															   else
															   { 
																   a._sortdsc(N)} 
															   for(var K=0; 
																   K<a.length; 
																   K++)
															   { 
																   O.push(typeof(a[K])=="object"?a[K].name:a[K])} 
															   return O} 
														   ; 
														   a.top=function(L,M)
														   { 
															   if(!M)
															   { 
																   M="score"} 
															   a._sortdsc(M); 
															   var N=[]; 
															   for(var K=0; 
																   K<Math.min(L||1,a.length); 
																   K++)
															   { 
																   N.push(a[K].name)} 
															   return N} 
														   ; 
														   a.filter=function(N)
														   { 
															   var M=[]; 
															   for(var L=0; 
																   L<a.length; 
																   L++)
															   { 
																   for(var K in N)
																   { 
																	   if(typeof(N[K])!="function")
																	   { 
																		   if(a[L][K]==N[K])
																		   { 
																			   M.push(a[L])} 
																	   } 
																   } 
															   } 
															   return C(M)} 
														   ; 
														   return a} 
													   function v()
													   { 
														   _ate.ed.fire("addthis-internal.api",window.addthis||
														   { 
														   } 
														   ,
														   { 
call:"gti"} 
															   ); 
															   return C(j.interests)} 
													   function b()
													   { 
														   _ate.ed.fire("addthis-internal.api",window.addthis||
														   { 
														   } 
														   ,
														   { 
call:"gts"} 
															   ); 
															   return C(j.services)} 
													   function z()
													   { 
														   _ate.ed.fire("addthis-internal.api",window.addthis||
														   { 
														   } 
														   ,
														   { 
call:"gtt"} 
															   ); 
															   return I.track.ts.get()} 
													   function J()
													   { 
														   _ate.ed.fire("addthis-internal.api",window.addthis||
														   { 
														   } 
														   ,
														   { 
call:"gtl"} 
															   ); 
															   return j.location} 
													   function B(M)
													   { 
														   _ate.ed.fire("addthis-internal.api",window.addthis||
														   { 
														   } 
														   ,
														   { 
call:"isl"} 
															   ); 
															   var L=z(); 
															   if(L.type=="social")
															   { 
																   if(typeof(M)=="string")
																   { 
																	   M=M.split(","); 
																	   var a=
																	   { 
																	   } 
																	   ; 
																	   for(var K=0; K<M.length; K++)
																	   { 

																		   a[M[K]]=1
																	   } 

																	   if(!a[L.service])
																	   { 
																		   return false} 

																   } 
																   return true} 
															   return false} 
													   function G(K)
													   { 
														   _ate.ed.fire("addthis-internal.api",window.addthis||
														   { 
														   } 
														   ,
														   { 
call:"ish"
														   } 
														   ); 
														   var M=z(); 
														   if(M.type=="search")
														   { 
															   if(typeof(K)=="string")
															   { 

																	   K=K.split(","); 
																	   var L=
																	   { 
																	   } 
																	   ; 
																	   for(var a=0; a<K.length; a++)
																	   { 

																		   L[K[a]]=1} 
																	   if(M.terms&&M.terms.length)
																	   { 
																		   for(var a=0; 
																			   a<M.terms.length; 
																			   a++)
																		   { 
																			   if(!L[M.terms[a]])
																			   { 

																				   return false} 

																		   } 

																	   } 

																   } 

																   return true
															   } 

															   return false
													   } 

													   var t=
													   { 
ready:q,isReturning:function(a)
	  { 
	  } 
	  ,isOptedOut:c,isUserOf:D,hasInterest:o,isLocatedIn:i,interests:v,services:b,location:J} 
													   ; 
													   addthis.session=
													   { 
source:z,isSocial:B,isSearch:G} 
														   ; 
														   _ate.extend(r,t); 
														   return E(function(K,a)
														   { 
															   K[a]=(new y._Queuer(a)).call; 
															   return K
														   } 
														   ,r)
												   } 
												   )(); 
