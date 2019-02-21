# InlineAppStore

Need to show app store dialog inside current app like this:

![Demo inline dialog](/img/demo.png)

Fake KakaoTalk app that show inline app store dialog

![Fake KakaoTalk](/img/fake_kakao_talk.png)


## Conclusion

Dialog trên là một activity tên `com.google.android.finsky.activities.InlineAppDetailsDialog`, chạy trên process của chính app Google Play Store. (Nếu DISABLE app Google Play Store thì dialog sẽ không show được).

This feature of Play Store app is **exclusive for some selected Google's partners**

Google Play Store sẽ check package name của app muốn hiển thị dialog, nếu match với list partner apps thì show, nếu ko sẽ log lỗi `Called from untrusted package`

![Google play store app partner check](g_play_store_partner.png)



## Cách hiển thị dialog

- Tạo một `Intent(Intent.ACTION_VIEW)`
- Set data là Uri với dạng `market://details?id=com.zing.packagename`
- Gắn extras: `overlay` = `true`, `callerId` = package name của app hiện tại.
- Chỉ định package của intent thành `com.android.vending` (package name của app Google Play Store)
- `startActivityForResult()` với intent vừa tạo.

Intent đó sẽ mở app Google Play Store lên, `LaunchUrlHandlerActivity` sẽ bắt action. Sau đó show `InlineAppDetailsDialog` nếu caller app thuộc list Google partner, hoặc show `MainActivity` nếu caller là 1 app bình thường.



## Note

* List app nằm trong Google partner trong link S.O bên dưới.
* Đã test show thành công inline app store dialog với 1 app fake KakaoTalk (hình đính kèm), tuy nhiên không show được trong Zalo.



#### References:
- https://stackoverflow.com/questions/42734624/open-google-play-dialog-from-my-app
- https://qiita.com/84d010m08/items/e890f5250bfb5244fbe5
-https://github.com/ChiangC/FMTech/blob/master/GooglePlay6.0.5/app/src/main/java/com/google/android/finsky/activities/LaunchUrlHandlerActivity.java#L89 (source code chỗ handle intent của app Google Play Store)