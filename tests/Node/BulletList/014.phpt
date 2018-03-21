--TEST--
CommonMark\Node\BulletList isset tight
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

var_dump($list->tight);
var_dump(isset($list->tight));

$list->tight = true;

var_dump($list->tight);
var_dump(isset($list->tight));
?>
--EXPECT--
bool(false)
bool(true)
bool(true)
bool(true)
