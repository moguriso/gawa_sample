Function getArtworkAndPath()

        Dim objShell
        Dim tmp
        Dim iTunesApp
        Dim current
        Dim artworks
        Dim artwork
        Dim format
        Dim c_str

        Set objShell = CreateObject("WScript.Shell")
        tmp = objShell.ExpandEnvironmentStrings("%TMP%")

        Set iTunesApp = CreateObject("iTunes.Application")
        Set current = iTunesApp.CurrentTrack
        Set artworks = current.Artwork
        Set artwork = artworks.Item(1)
        format = artwork.Format

        Select Case format
        Case 1
                c_str = "jpg"
        Case 2
                c_str = "jpg"
        Case 3
                c_str = "jpg"
        End Select

        artwork.SaveArtworkToFile(tmp + "\\z." + c_str)
        getArtworkAndPath = tmp + "\\z."+ c_str

End Function

Function getTitle()

        Dim iTunesApp
        Dim current
        Dim name

        Set iTunesApp = CreateObject("iTunes.Application")
        Set current = iTunesApp.CurrentTrack
        name = current.Name

        getTitle = name

End Function

Sub playTrack()

        Dim iTunesApp

        set iTunesApp = CreateObject("iTunes.Application")
        iTunesApp.Play

End Sub

Sub nextTrack()

        Dim iTunesApp

        set iTunesApp = CreateObject("iTunes.Application")
        iTunesApp.NextTrack

End Sub

'msgbox("Hello World")
'WScript.Echo "Hello World"

'Dim ret

'playTrack
'nextTrack
'ret = getArtworkAndPath

'ret = getTitle
'msgbox(ret)

