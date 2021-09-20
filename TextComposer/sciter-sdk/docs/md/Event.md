### class Event

#### properties:

* `event.bubbles`
* `event.cancelable`
* `event.currentTarget`
* `event.defaultPrevented`
* `event.eventPhase`
* `event.target`
* `event.type`
* `event.data`
* `event.details`
* `event.keyCode`
* `event.code` string representation of keyCode "KeyENTER", "KeyF1"...
* `event.altKey` true/false
* `event.ctrlKey`
* `event.metaKey`
* `event.shiftKey`
* `event.button`
* `event.buttons`
* `event.clientX`
* `event.clientY`
* `event.screenX`
* `event.screenY`

* `event.deltaX:float` - wheel deltas
* `event.deltaY:float`
* `event.deltaMode|int` - 0 - deltaX/Y are pixels coming from touch devices, 1 - deltaX/Y are in "lines" (a.k.a. mouse wheel "ticks"). 


#### properties (Sciter specific):

* `event.x` - sciter specific, coordinates are relative
* `event.y` - to `event.currentTarget` - the element this event handler is attached to.
* `event.source` - used in some events to indicate auxiliary "source" element. 
* `event.isOnIcon:Element` - mouse events, it is set to element when mouse is on icon of that element. Element icon is an element's foreground-image (if any) so event.isOnIcon is on when mouse is over area where the image is rendered.

#### methods:

* `event.preventDefault()`
* `event.stopImmediatePropagation()`
* `event.stopPropagation()`


### Known Events

#### Mouse

* `mousemove`
* `mouseenter`
* `mouseleave`
* `mouseidle` - mouse stays not moving in the element, the event triggers tooltip show.
* `mousetick` - mouse is pressed for some time in element, periodic event
* `mousedown`
* `mouseup`
* `mousewheel`
* `mousedragrequest`
* `dblclick` | `doubleclick`
* `tripleclick`

#### Behaviors

* `click`
* `input` - posted event, arrived after user changes something.
* `change` - synchronous event, arrived on user's change and before screen update.
* `press` 
* `changing` 
* `submit` 
* `reset`  
* `expand`  
* `collapse`  
* `statechange` 
* `visualstatechange` 
* `disabledstatechange` 
* `readonlystatechange` 

* `contextmenu` - context menu request for the element
* `contextmenusetup` - notification to setup context menu, context menu DO< element is event.source

* `animationend`
* `animationstart` 
* `animationloop` 

* `transitionend`
* `transitionstart` 

* `mediachange` 
* `contentchange` 
* `inputlangchange` 
* `pastehtml` 
* `pastetext` 
* `pasteimage` 
* `popuprequest`  
* `popupready`    
* `popupdismissing` 
* `popupdismissed`  

* `tooltiprequest` 

#### Focus

* `focusin`
* `focusout` 
* `focus` 
* `blur` 

#### Keyboard

* `keydown`
* `keyup`  
* `keypress`
* `compositionstart`
* `compositionend`

#### Scroll

* `scroll`
* `scrollanimationstart` 
* `scrollanimationend` 

#### Document lifecycle

Loading:

* `parsed` - document just got a DOM structure, scripts are not run yet. This event can be handled by document container only (window or frame). 
* `ready` | `DOMContentLoaded` - document loaded, DOM is parsed, scripts are loaded and run.
* `complete` - document loaded in full scripts wer run, all resources defined in HTML are loaded.

Closing:

* `close` | `unload` - document is closed and about to be deleted soon.
* `beforeunload` - document is about to be unloaded, script namespace is still operational.
* `closerequest` - first phase of document closure, it can be rejected at this point by calling `event.preventDefault()`.

#### Element's state change

* `sizechange` - change of element dimensions, use `element.onsizechange = function() {}` to setup the event handler;
* `visibilitychange` -  - change of element visibility status,  use `element.onvisibilitychange = function() {}` to setup the event handler;

#### Image 

* `load`
* `error`

#### Pager (print preview)

* `paginationstart`
* `paginationpage` 
* `paginationend` 

#### Drag-n-drop

* `drag`
* `dragenter` 
* `dragleave` 
* `drop` 
* `dragcancel` 
* `dragaccept` 
* `willacceptdrop`

#### Video 

* `play`
* `ended`

* `videocoordinate`
* `videoframeready`

## MISC

- [Event handling in Sciter](https://sciter.com/event-handling-in-sciter/)
