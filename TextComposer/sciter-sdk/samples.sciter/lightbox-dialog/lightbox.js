/*
  var r = lightbox(<dialog>
    <header>...</header>
    <form>...</form>
    <footer>
      <button #ok>OK</button>
    </footer>
  </dialog>);
 */
 
export function lightbox(jsxDialog)
{
  // check if it has styleset defined
  if(!jsxDialog[1].styleset)
    jsxDialog[1].styleset = __DIR__ + "lightbox.css#dialog";

  document.body.append(jsxDialog);
  
  var dlg = document.body.lastElementChild; // our dialog layer
  
  var retval = null; // value to return

  function handleValue(button)  
  {
    retval = button.id;
    if(retval == "ok") {
      let rv = dlg.value || dlg.$("form")?.value;
      if(rv !== undefined) retval = rv;
    } else if(retval == "cancel")
      retval = undefined;
    dlg.state.collapsed = true; // to signal that we are done with it.
  }
  
  // setup control event handler
  dlg.on("click", "footer>button", function(evt, button)
  {
    handleValue(button);
    return true;
  });

  // setup keyboard event handler
  dlg.on("keydown", function(evt) {
    var cmd;
    console.log(evt.code);
    if( evt.code == "KeyESCAPE" )
      cmd = "cancel";
    else if( evt.code == "KeyRETURN" )
      cmd = "ok";
    else 
      return; // we handle only ESCAPE and ENTER here.

    var button = dlg.$(`footer>button#${cmd}`);
    if( button )
    {
      handleValue(button);
      return true;
    }
  });
  
 
  // and finally run the modal loop:
  
  dlg.state.expanded = true;

  document.body.classList.add("dialog-shown");

  dlg.post( () => dlg.classList.add("shown") );

  var wnd = Window.this;

  var savedFocus = wnd.focus;
  wnd.eventsRoot = dlg;
  while (!dlg.state.collapsed && wnd.state != Window.WINDOW_HIDDEN) 
     wnd.doEvent();
  wnd.eventsRoot = null;
  wnd.focus = savedFocus;
  
  dlg.remove(); // remove it from the DOM
  document.body.classList.remove("dialog-shown");
  
  return retval;
}

export function lightboxAsync(jsxDialog)
{
  // check if it has styleset defined
  if(!jsxDialog[1].styleset)
    jsxDialog[1].styleset = __DIR__ + "lightbox.css#dialog";

  document.body.append(jsxDialog);
  
  var dlg = document.body.lastElementChild; // our dialog layer
  
  var retval = null; // value to return
  var savedFocus = null;
  var closeCallback = null;

  function close() {
    wnd.eventsRoot = null;
    wnd.focus = savedFocus;
    dlg.remove(); // remove it from the DOM
    document.body.classList.remove("dialog-shown");
    if(typeof closeCallback == "function")
      closeCallback(retval);
  }
  
  function handleValue(button)
  {
    retval = button.id;
    if(retval == "ok") {
      let rv = dlg.value || dlg.$("form")?.value;
      if(rv !== undefined) retval = rv;
    } else if(retval == "cancel")
      retval = undefined;
    close();
  }
  
  // setup control event handler
  dlg.on("click", "footer>button", function(evt, button)
  {
    handleValue(button);
    return true;
  });

  // setup keyboard event handler
  dlg.on("keydown", function(evt) {
    var cmd;
    if( evt.code == "KeyESCAPE" )
      cmd = "cancel";
    else if( evt.code == "KeyRETURN" )
      cmd = "ok";
    else 
      return; // we handle only ESCAPE and ENTER here.
      
    var button = dlg.$(`footer>button#${cmd}`);
    if( button )
    {
      handleValue(button);
      return true;
    }
  });
 
  // just show it without modal loop 
  dlg.state.expanded = true;

  document.body.classList.add("dialog-shown");

  dlg.post( () => dlg.classList.add("shown") );

  var wnd = Window.this;

  savedFocus = wnd.focus;
  wnd.eventsRoot = dlg;
   
  return {
    close: () => { retval = undefined; close(); },
    set onclose(v) { closeCallback = v; }
  };
}

