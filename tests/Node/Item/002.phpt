--TEST--
CommonMark\Node fetch Item
--FILE--
<?php
$md = <<<MD
  * item 1
  * item 2
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

$list = $doc->firstChild;

$item = $list->firstChild;

if ($list instanceof CommonMark\Node\BulletList &&
    $item instanceof CommonMark\Node\Item) {
	echo "OK";
}
?>
--EXPECT--
OK
