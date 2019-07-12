# Database-System-Implementation
## تشخیص ویژگی‌های سریال‌پذیری، قابل احیا و پاد آبشاری برای یک زمانبندی
<p dir='rtl' align='right'>این برنامه برای یک زمانبندی داده شده تشخیص می دهد آیا زمانبندی هر یک از سه ویژگی سریال‌پذیری، قابلیت احیا و پادآبشاری را دارد یا نه.</p>
<p dir='rtl' align='right'> برای تست ویژگی سریالپذیری از گراف تقدم استفاده می کنیم. و برای تست دو ویژگی دیگر از تعریف آنها استفاه می کنیم.
  مثلا اگر در یک زمانبندی تراکنش T1 داده X را بنویسد و در ادامه تراکنش T2 همان داده‌ (یعنی X) را بخواند، اگر Commit تراکنش T2 قبل از Commit یا Abort تراکنش T1 آمده باشد آنگاه ویژگی قابلیت احیا وجود ندارد. در مورد ویژگی پادآبشاری نیز به همین ترتیب از تعریف آن استفاده می کنیم.</p>
  
### ورودی
<p dir='rtl' align='right'>سطر اول ورودی عدد صحیح nn است که تعداد اعمال زمانبندی را نشان می‌دهد (0<n<10000<n<1000). در nn سطر بعدی در هر سطر یک عمل از زمانبندی قرار دارد. هر عمل زمانبندی یکی از اعمال خواندن، نوشتن، Commit یا Abort است که یکی از تراکنش ها انجام می دهند. بنابراین اولین کاراکتر هر سطر کاراکتر T است و دو کاراکتر بعدی شماره تراکنش را نشان می‌دهند. کاراکتر چهارم یکی از چهار کاراکتر R، W، C یا A است که نشان دهنده یکی از چهار عمل خواندن، نوشتن، commit یا Abort است و در صورتی که کاراکتر چهارم R یا W باشد کاراکتر پنجم نیز اسم اقلام داده که عمل خواندن یا نوشتن روی آن انجام می‌گیرد را نشان می‌دهد. برای مثال T01WX به این معنی است که تراکنش 1 داده X را می‌نویسد. و T12A به این معنی است که تراکنش 12‌ام Abort می‌کند.
</p>
