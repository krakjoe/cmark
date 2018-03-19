--TEST--
CommonMark\Render CommonMark Width
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
hello world
EOD
);

echo CommonMark\Render($doc, CommonMark\Render\Normal, 4);
?>
--EXPECT--
hello
world

