## SSO

单点登录。单独维护的一个登录系统，完成登录认证后，服务端中该用户对应的session中标记登录状态为yes，同时在浏览器中写入cookie，下次再访问该应用的时候，请求中带上cookie，服务器根据cookie找到对应的session，判断用户是否登录。



## 同域下的单点登录

域名：app1.a.com	app2.a.com	sso.a.com

在sso.a.com中登录了，其实是在sso.a.com的服务端的session中记录了登录状态，同时在浏览器的sso.a.com下写入了cookie，如何在app1.a.com和app2.a.com登录呢？

1. cookie不能跨域，cookie的domain属性为sso.a.com，在给app1.a.com和app2.a.com发送请求是带不上的
2. Sso，app1，app2是不同的应用，它们的session存在自己的应用内，不共享

针对第一个问题：sso登录以后，将cookie的域设置为顶域，这样所有的子域都可以访问到顶域的cookie。设置cookie时，只能设置顶域和自己的域，不能设置其他的域。

针对第二个问题：再访问app1时，cookie也带到了app1的服务端，app1服务端怎么找到对应的session？需要把三个系统的session共享，比如spring-session

同域下的单点登录巧用了cookie顶域的特性。

## 不同域下的单点登录

CAS流程：

1. 用户访问app系统，app系统需要登录，但用户现在没有登录
2. 跳转到CAS server，即SSO登录系统，SSO系统也没有登录，弹出用户登录页
3. SSO系统认证后，将登录状态写入SSO的session，浏览器中写入SSO域下的cookie
4. SSO系统登录完成后会生成一个ST（service ticket），然后跳转到app系统，同时将ST作为参数传递给app系统
5. app系统拿到ST后，从后台向SSO发送请求，验证ST是否有效
6. 验证通过后，app系统将登录状态写入session并设置app域下的cookie

接下来，用户访问app2系统时的流程：

1. 用户访问app2系统，app2系统没有登录，跳转到SSO
2. 由于SSO以及登录了，不需要重新登录认证
3. SSO生成ST，浏览器跳转到app2系统，并将ST作为参数传递给app2
4. app2拿到ST，后台访问SSO，验证ST是否有效
5. 验证成功后，app2将登录状态写入session，并在app2域下写入cookie


