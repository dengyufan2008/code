from musicdl import musicdl
# music_client = musicdl.MusicClient(music_sources=['MiguMusicClient', 'NeteaseMusicClient', 'QQMusicClient', 'KugouMusicClient', 'KuwoMusicClient', 'QianqianMusicClient'])
music_client = musicdl.MusicClient(music_sources=['NeteaseMusicClient'])
music_client.startcmdui()
