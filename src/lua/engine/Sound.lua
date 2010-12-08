-- Sound management functions for CC/Lua

Sound = {
	-- if done on the server, a message is sent to clients to play the sound
	play = function (_name, position, volume, clientNumber)
		position = defaultValue(position, Vector3(0, 0, 0))
		volume = defaultValue(volume, 0)

		if Global.CLIENT then
			CAPI.playSoundByName(_name, position.x, position.y, position.z, volume)
		else
			-- TODO - don't send if client is too far to hear
			-- warn when using non-compressed names
			if string.len(_name) > 2 then
				log(WARNING, string.format("Sending a sound '%s' to clients using full string name. This should be done rarely, for bandwidth reasons.", _name))
			end
			clientNumber = defaultValue(clientNumber, MessageSystem.ALL_CLIENTS)
			MessageSystem.send(clientNumber, CAPI.SoundToClientsByName, position.x, position.y, position.z, _name, -1)
		end
	end,

	stop = function (_name, volume, clientNumber)
		volume = defaultValue(volume, 0)

		if Global.CLIENT then
			CAPI.stopSoundByName(_name, volume)
		else
			-- warn when using non-compressed names
			if string.len(_name) > 2 then
				log(WARNING, string.format("Sending a sound '%s' to clients using full string name. This should be done rarely, for bandwidth reasons.", _name))
			end
			clientNumber = defaultValue(clientNumber, MessageSystem.ALL_CLIENTS)
			MessageSystem.send(clientNumber, CAPI.SoundStopToClientsByName, volume, _name, -1)
		end
	end,

	playMusic = CAPI.music,

	setMusicHandler = function(func)
		Sound.musicHandler = func
		Sound.musicCallback() -- start playing now
	end,

	musicCallback = function()
		if Sound.musicHandler then
			Sound.musicHandler()
		end
	end,

	register = function(sound, vol)
		vol = defaultValue(vol, 0)
		CAPI.registerSound(sound, vol)
	end,

	reset = CAPI.resetSound
}
