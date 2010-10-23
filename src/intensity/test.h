/**
 * @defgroup Meh_Group Meh
 *
 * @{
 */

/**
 * @brief blablablah
 * @param uniqueId blargh
 * @param kwargs mehbar
 * @return fooobar
 * 
 * Gets an item on -1 and creates and returns a reference -
 * that's an unique number which can be later re-used.
 * The item gets pop'd from stack after ref'ing it.
 * 
 * Reference can be later used to get the item again at any place.
 * @see getRef()
 * @see unref()
 */
function AnimatableLogicEntity:foo(uniqueId, kwargs)
{
	self.__parent.init(self, uniqueId, kwargs)
	self._attachmentsDict = {}
	self.modelName = ""
	self.attachments = {}
	self.animation = CMath.bor(ANIM_IDLE, ANIM_LOOP)
	log(DEBUG, "Animatable.init done")
}


/**
 * @}
 */
