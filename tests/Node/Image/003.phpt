--TEST--
CommonMark\Node\Image constructor
--FILE--
<?php
$image = new CommonMark\Node\Image("url", "title");

var_dump(
	$image->url, 
	$image->title);
?>
--EXPECT--
string(3) "url"
string(5) "title"
