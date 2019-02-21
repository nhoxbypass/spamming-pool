package com.kakao.talk

import android.content.Context
import android.content.Intent
import android.net.Uri
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*


class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btn_open_inline_app_dialog.setOnClickListener {
            val i = getIntentOpenInlineAppDialog(this, et_package_name.text.toString(), 524288)
            if (ensureDirectMarketIntent(i)) {
                startActivityForResult(i, 979)
            } else {
                startActivity(i)
            }
        }

        btn_open_play_store.setOnClickListener {
            openGooglePlay(this, et_package_name.text.toString())
        }
    }


    /* renamed from: a */
    fun getIntentOpenInlineAppDialog(context: Context, str: String, i: Int): Intent {
        var intent = Intent(
            Intent.ACTION_VIEW,
            Uri.parse(String.format(Locale.US, "market://details?id=%s", str))
        )
        intent.addFlags(i)
        intent = addExtras(intent)
        return if (canHandleIntent(context, intent)) {
            intent
        } else Intent(
            Intent.ACTION_VIEW,
            Uri.parse(String.format(Locale.US, "https://play.google.com/store/apps/details?id=%s", str))
        ).addFlags(i)
    }

    /* renamed from: a */
    fun addExtras(intent: Intent): Intent {
        intent.putExtra("overlay", true)
        intent.putExtra("callerId", packageName)

        intent.setPackage("com.android.vending") // package name of Google Play Store app

        return intent
    }

    fun canHandleIntent(context: Context?, intent: Intent): Boolean {
        val info = context!!.packageManager.queryIntentActivities(intent, 65536)
        return info != null && info.size > 0
    }


    fun ensureDirectMarketIntent(intent: Intent): Boolean {
        if (intent.data != null) {
            val data = intent.data
            if ("market" != data!!.scheme) {
                if (data.toString().matches("http(s)?://play\\.google\\.com/store/apps/details.+".toRegex())) {
                    for (str in data.queryParameterNames) {
                        if ("id" != str && "referrer" != str) {
                            return false
                        }
                    }
                    intent.data =
                        Uri.parse(
                            data.toString().replaceFirst(
                                "http(s)?://play\\.google\\.com/store/apps/details".toRegex(),
                                "market://details"
                            )
                        )
                }
            }
            addExtras(intent)
            return true
        }
        return false
    }

    fun openGooglePlay(context: Context, packageName: String) {
        try {
            val intent = Intent(Intent.ACTION_VIEW)
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK)
            intent.data = Uri.parse("market://details?id=$packageName")
            context.startActivity(intent)
        } catch (anfe: android.content.ActivityNotFoundException) {
            // open play store in browser
            try {
                context.startActivity(
                    Intent(
                        Intent.ACTION_VIEW,
                        Uri.parse("https://play.google.com/store/apps/details?id=$packageName")
                    )
                )
            } catch (ex: Exception) {
                ex.printStackTrace()
            }

        } catch (ex: Exception) {
            ex.printStackTrace()
        }
    }
}
